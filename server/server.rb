require 'socket'
require 'erb'

class HttpServer
  def initialize(session, request, basePath)
    @session = session
    @request = request
    @basePath = basePath
  end

  def getFullPath()
    fileName = nil
    if @request =~ /GET .* HTTP.*/
      fileName = @request.gsub(/GET /, '').gsub(/ HTTP.*/, '')
    end
    fileName = fileName.strip
    unless fileName == nil
      fileName = @basePath + fileName
      fileName = File.expand_path(fileName, @defaultPath)
      #fileName.gsub!('/', '\\')
    end
    fileName << "/index.html" if  File.directory?(fileName)
		return fileName
  end

	def getContentType(path)
    #TODO replace with access to HKEY_CLASSES_ROOT => "Content Type"
    ext = File.extname(path)
    return "text/html"  if ext == ".html" or ext == ".htm"
    return "text/plain" if ext == ".txt"
    return "text/css"   if ext == ".css"
    return "image/jpeg" if ext == ".jpeg" or ext == ".jpg"
    return "image/gif"  if ext == ".gif"
    return "image/bmp"  if ext == ".bmp"
    return "text/plain" if ext == ".rb"
    return "text/xml"   if ext == ".xml"
    return "text/xml"   if ext == ".xsl"
    return "text/html"
  end

  def serve()
    @fullPath = getFullPath()
		src = nil
    begin
      if File.exist?(@fullPath) and File.file?(@fullPath)
				
        if @fullPath.index(@basePath) == 0 #path should start with base path
          contentType = getContentType(@fullPath)
          @session.print "HTTP/1.1 200/OK\r\nServer: Makorsha\r\nContent-type: #{contentType}\r\n\r\n"
          src = File.open(@fullPath, "rb")
	        while (not src.eof?)
            buffer = src.read(256)
            @session.write(buffer)
          end
          src.close
          src = nil
        else
          # should have sent a 403 Forbidden access but then the attacker knows that such a file exists
          @session.print "HTTP/1.1 404/Object Not Found\r\nServer: Makorsha\r\n\r\n"
        end
      else
        @session.print "HTTP/1.1 404/Object Not Found\r\nServer: Makorsha\r\n\r\n"
      end
    ensure
      src.close unless src == nil
			@session.close
    end
  end

end

def logger(message)
  logStr =  "\n\n======================================================\n#{message}"
  puts logStr
  $log.puts logStr unless $log == nil
end

basePath = File.expand_path("../web/")
server = TCPServer.new(3500)
logfile = basePath + "/log.txt"
$log = File.open(logfile, "w+")

loop do
  session = server.accept
  request = session.gets
  logStr =  "#{session.peeraddr[2]} (#{session.peeraddr[3]})\n"
  logStr += Time.now.localtime.strftime("%Y/%m/%d %H:%M:%S")
  logStr += "\n#{request}"
  logger(logStr)

  Thread.start(session, request) do |session, request|
    HttpServer.new(session, request, basePath).serve()
  end
end
log.close

