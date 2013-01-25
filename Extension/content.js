$(document).ready(function() {
	console.log("Hello World!");
	var srcList = $('img').filter(function(){
		return ($(this).width() > 200 || $(this).height() > 200);
	});

	function addMessageSender( sUrl, element ) {
		chrome.extension.sendMessage({url: sUrl},function(response) {
			element.removeClass("tint");
			if($.trim(response.farewell) == "comic" ){
				console.log("This is a comic");
				element.remove();
			} else {
				console.log("This is not a comic");
				console.log(element);
			}
		});
	}

	for(var i = 0; i < srcList.length; i++) {
		console.log(srcList[i].src);
		var srcURL = srcList[i].src;

		var style = document.createElement('link');
		style.rel = 'stylesheet';
		style.type = 'text/css';
		style.href = chrome.extension.getURL('mystyles.css');
		document.head.appendChild(style);

		var curid = i.toString();
		$(srcList[i]).attr( 'id', curid );
		var curElement = $("#" + curid);
		curElement.addClass("tint");
		addMessageSender( srcURL, curElement );
	}
});
