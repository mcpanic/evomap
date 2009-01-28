require 'Dictionary'

class Graph
		
		@@dictionary = Dictionary.new

	def initialize(graph)
		# turn graph into tree
		@graph = graph
		@visited = {}

	end

	def save(sessionid, generation, mapid)
		dir = "/maps/#{sessionid}"
		path = dir + "/#{generation.to_s.rjust(3,"0")}_#{mapid.to_s.rjust(2,"0")}.xml"
		Dir.mkdir("public" + dir) unless File.directory?("public" + dir)
		root = ''
		@graph.each do |key,value|
			root = key 
			break	
		end
		xml = '<?xml version="1.0" encoding="ISO-8859-1"?>'
		xml += "\n"
		xml +=  create_xml root
		
		File.open("public" + path, "w") do |f|
			f.puts xml	
		end
		path
	end

	def create_xml(nodeid)
		xml = ''
		xml	+= <<-EOF
		<node>
			<label><![CDATA[#{@@dictionary.lookup(nodeid)}]]></label>
			<url><![CDATA[#{nodeid}]]></url>
		EOF
		
			xml+= "<children>"
			@graph[nodeid].each do |adjid|
				next if @visited[nodeid+'-'+adjid]
				@visited[nodeid+'-'+adjid] = true
				xml += create_xml adjid
			end	
			xml+="</children>"
		
		xml+="</node>"

		return xml
	end
end
