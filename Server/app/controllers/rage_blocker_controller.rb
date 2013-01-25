class RageBlockerController < ApplicationController
  def blocker
	url = params[:src]

	require 'open-uri'
	open('image.jpg', 'wb') do |file|
		file << open(url).read
	end
	
	result = `./online image.jpg`
	
	respond_to do |format|
		format.json { render :text => result }
	end
  end
end
