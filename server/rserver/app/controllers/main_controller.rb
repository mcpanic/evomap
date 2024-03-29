class MainController < ApplicationController
	require 'GASession'
	require 'Graph'

	def index
		# erb provides button to evaluate with 'start' argument
				
	end

	def evaluate
		case params[:stage]
			when "start" 	# reset
				@gasession = GASession.new(Time.now.to_i) # START GA
				session[:sid] = @gasession.sid
			else 	# run
				@gasession = GASession.get(session[:sid])
		end
	
		@graph = @gasession.step(params[:prevscore])	# continue ga	
		
		if @gasession.generation % 10 != 0
			while(@gasession.generation % 10 != 0)
				@gasession.step_NN	
			end
		end

		@finishing = @gasession.finishing?
		graph = Graph.new(@graph)
		@generation = @gasession.generation
		@mapid = @gasession.mapid
		@test_score = @gasession.test_score
	
		@filepath = graph.save(session[:sid],@generation,@mapid)
		
	end

	def finish
		GASession.get(session[:sid]).step(params[:prevscore])
		GASession.close(session[:sid])
		session[:sid] = nil
	end
end
