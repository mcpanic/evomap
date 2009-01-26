class GASession
	@@active_sessions = {}

	attr_accessor :sid
	
	def initialize(timestamp)
		@sid = timestamp
		@@active_sessions[@sid] = self
		@proc = open("|../../generation/list/evolve")
	  
	end

	def step
		@graph = {} # graph is a hash, with nodeid -> hash
		# READ 
		str = ''
		flag = true
		while flag
			str = gets
			if str == "\n"
				flag = false
			else 
				arr = str.split(' ')
				curnode = 0
				arr.each do |e|
					if @graph[e].nil?
						@graph[e] = Array.new
						curnode = e
					else
						@graph[curnode].push(e)
					end
				end
				puts "\n"
			end
		end
		return @graph		
	end


	def self.close(sid)
		@@active_sessions[sid] = nil
	end

	def self.get(sid)
		@@active_sessions[sid]
	end
end
