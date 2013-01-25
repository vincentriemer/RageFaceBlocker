chrome.extension.onMessage.addListener( function(request, sender, sendResponse) {
		var srcURL = request.url.replace( '/s480x480', '' );
		console.log("FooBar");
		$.ajax({
			url: 'http://localhost:3000/rage_blocker/blocker.json',
			dataType: 'text',
			async: false,
			data: { "src": srcURL },
			success: function(text) {
				console.log(text);
				sendResponse({farewell: text});
			}
		});
});


