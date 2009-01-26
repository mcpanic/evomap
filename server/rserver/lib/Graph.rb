class Graph

	def initialize(graph)
		@graph = graph
	end

	def save(sessionid, generation, mapid)
		dir = "public/maps/#{sessionid}"
		path = dir + "/#{generation.to_s.rjust(3,"0")}_#{mapid.to_s.rjust(2,"0")}.xml"
		Dir.mkdir(dir) unless File.directory?(dir)
		File.open(path, "w") do |f|
			f.puts "xml" # write graph	
		end
		path
	end
end
