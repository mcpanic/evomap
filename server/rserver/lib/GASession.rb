require 'Dictionary'
require 'NN'

class GASession
	@@active_sessions = {}

	attr_accessor :sid
	
	def initialize(timestamp)
		@sid = timestamp
		@@active_sessions[@sid] = self
		@proc = open("|../../generation/list/evolve	#{Dictionary.size}","w+")
	  @generation = 0
		@mapid = 0
		@finishing = false
		@nn = NN.new
		@test_score = 0
	end

	def recv_graph
		@graph = {} # graph is a hash, with nodeid -> hash
		# READ 
		str = ''
		flag = true
		while flag
			str = @proc.gets
			puts str
			if str == "end\n" ## end condition 
				flag = false
			elsif str == "finishing\n"
				flag = false
				@finishing = true
			elsif	str =~ /generation [0-9]+.*/  ## new generation
				@generation = /generation ([0-9]+)/.match(str)[1].to_i + 1
				@mapid = 0
			else ## retrieve graph
				arr = str.split(' ')
				curnode = nil
				arr.each do |e|
					if curnode.nil?
						curnode = e
					end
					
					if @graph[curnode].nil?
						@graph[e] = Array.new
						curnode = e
					else
						@graph[curnode].push(e)
					end
				end
			end
		end

		@mapid = @mapid + 1
		return @graph
	end

	def step_NN
		recv_graph
		score = @nn.eval(@graph)
		@proc.puts score
		puts "entered #{score}"
	end

	def step(prevscore)
		unless prevscore.nil?
			@proc.puts prevscore # feed in score
			puts "entered #{prevscore}"
			@nn.train(@graph,prevscore)
			@test_score = @nn.eval(@graph)
		end
		recv_graph
	end

	def finishing?
		@finishing
	end

	def generation
		@generation
	end

	def mapid
		@mapid
	end

	def sid
		@sid
	end

	def test_score
		@test_score
	end

	def close
		@proc.close unless @proc.nil?
	end

	def self.close(sid)
		session = @@active_sessions[sid]
		session.close
		@@active_sessions[sid]= nil	
	end

	def self.get(sid)
		@@active_sessions[sid]
	end
end
