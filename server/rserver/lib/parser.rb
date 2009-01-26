str = ''
flag = true
while flag
	str = gets
	if str == "\n"
		flag = false
	else 
		arr = str.split(' ')
		arr.each do |e|
			print "[" + e + "]"
		end
		puts "\n"
	end
end
