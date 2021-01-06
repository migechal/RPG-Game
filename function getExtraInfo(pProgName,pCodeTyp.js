function getExtraInfo(pProgName,pCodeType,pCodeField,pExtraField) {
    var vCodeField;
    if (typeof(pCodeField) === 'string') {
        vCodeField = pCodeField;
    } else if (typeof(pCodeField) === 'object'){
        vCodeField = pCodeField.id;
    }
    if (vCodeField) {
        gCheckEels[vCodeField] = false;
    }
   function continueGetExtraInfo() {
       var tmpEl;
      //delay so that 2 processing at the same time don't overlap each other
      if (gOpenRequest) {
          window.setTimeout(continueGetExtraInfo, 100);
      } else {
         if (gLoginMessage != '') {
            showMessage(gLoginMessage);
            //gLoginMessage = '';
         } else if (pProgName != 'qbrwshttp001.w' && pProgName != 'qprnthttp002.w' && pProgName != 'sgradhttp026.w' && pProgName != 'qgrphhttp001.w') {
             //showMessage('Retrieving data...');
         }
         gOpenRequest = true;
         if (tmpEl = document.getElementById(pExtraField)) {
             pExtraField = tmpEl;
         }
         gExtraHandle = pExtraField;

         if (pCodeField != '' && document.getElementById(pCodeField)) {
             gCodeValue = getFieldValue(pCodeField);
         } else {
             gCodeValue = pCodeField;
         }
         abortHttpRequest(false);
         gAbortExtraInfo = false;
         gExtraInfoXmlHttp  = XmlHttp.create();
         if (gExtraInfoXmlHttp) {
             gExtraInfoXmlHttp.open("POST",pProgName,true);
             gExtraInfoXmlHttp.onreadystatechange = function () {
                if (gAbortRequests || gAbortExtraInfo) {
                    if (gLoginMessage!='') {
                         gLoginMessage = '';
	                     hideMessage();
	                 }
                    if (vCodeField) {
                        gCheckEels[vCodeField] = true;
                    }
                    return;
                }
              var vExtraInfo;
              if (gExtraInfoXmlHttp.readyState == 4) {
                  gOpenRequest = false;
			  	if (gExtraInfoXmlHttp.status == 200) {
	                 vExtraInfo=getData('extra',gExtraInfoXmlHttp.responseText);
                     try {
                         if (pExtraField != '') {
                             if (pExtraField.id == 'sFilterList') {
                                 $('#sFilterSelect').replaceWith(vExtraInfo);
                             } else {
                                 pExtraField.value = vExtraInfo;
                             }

							 if (pExtraField.innerHTML && pExtraField.tagName != "SELECT" && pExtraField.tagName != "TEXTAREA") {
    	                        if (vExtraInfo == '') {
    	                            vExtraInfo='&nbsp;';
    	                        }
    	                        $(pExtraField).html('&nbsp');
    	                        //prevents scrolling data issue
    	                        if (vExtraInfo.indexOf("'")==-1) {
    	                            window.setTimeout(function(){dispHTMLinfo(pExtraField.id,vExtraInfo)}, 1);
    	                        } else {
    	                            $(pExtraField).html(vExtraInfo);
    	                        }
                                if (pExtraField.id == 'dFilterDetails') {
                                    showFilterDetailTip();
                                } else if (pExtraField.id == 'dChartDetails') {
                                    showChartDetailTip();
                                }
    	                     }
    	                 }
                     }
                     catch(er) {}
	                 
	                 if (gLoginMessage!='' /*|| (pProgName!='qbrwshttp001.w' && pProgName!='qprnthttp002.w')*/ ) {
                         gLoginMessage = '';
	                     hideMessage();
	                 }
	                 if (window.customExtraInfo) {
                         vExtraInfo = vExtraInfo.replace(/&#x005B;/gi, "[").replace(/&#x005D;/gi, "]");
	                     customExtraInfo(pCodeType,vExtraInfo,pExtraField);
	                 }
	                 if (pCodeType=='filterList') {
	                    if (gApplyFilter==true) {
	                        processSearch(document.getElementById("CurrentProgram").value,"applyFilter");
	                    }
	                 } else if (pCodeType=='chartList') {
	                     getChartDetail();
                         if (gApplyFilter == true) {
                             openChartWindow('create');
                             gApplyFilter = false;
                         }
	                 }
                     if (vCodeField) {
                        gCheckEels[vCodeField] = true;
                     }
	              }
			  }
           }
           var vParams = "requestAction=eel&method=extrainfo&codeType=" + pCodeType + "&codeValue=" + encodeURIComponent(gCodeValue) +  buildFormData();
           gExtraInfoXmlHttp.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded');
           if (gIsMoz || gIsIE) {
               gExtraInfoXmlHttp.setRequestHeader("Connection", "close");
               gExtraInfoXmlHttp.setRequestHeader("Content-length", vParams.length);
           }
           gExtraInfoXmlHttp.send(vParams);


         } else {
             gOpenRequest = false;
         }
         return false;
      }
   }
   //delayed here as well to prevent first process that fires from having issues in firefox
   if (!gOpenRequest) {
       window.setTimeout(continueGetExtraInfo, 100);
   } else {
       continueGetExtraInfo();
   }
}