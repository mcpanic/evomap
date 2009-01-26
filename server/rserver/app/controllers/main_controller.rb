class MainController < ApplicationController
	require 'GASession'

	def index
		# erb provides button to evaluate with 'start' argument
				
	end

	def evaluate
		case params[:action]
			when "start" # reset
				@gasession = GASession.new(Time.now.to_i) # START GA
				session[:sid] = gasession.sid
				render :action => 'start'
			else # run
				@gasession = GASession.get(session[:sid])
				graph = @gasession.step	# continue ga


		end
	end

	def finish
		GASession.close(session[:sid])
		session[:sid] = nil
		render :action => 'start'
	end
end
