require 'rubygems'
require 'ruby_fann/neural_network'


class Fann
	def initialize
			@fann = RubyFann::Standard.new(
			:num_inputs=>300, 
			:hidden_neurons=>[10, 10, 10, 10], 
			:num_outputs=>1)

	end

	def run
	
# Create Training data with 2 each of inputs(array of 3) & desired outputs(array of 1).
		inputs = []
		outputs =[]

		0.upto(9) do |p|
			arr = Array.new
			inputs.push(arr)
			0.upto(299) do |i|
				arr.push(rand())
			end
			arr = Array.new
			arr.push(rand())
			outputs.push(arr)
		end

		puts inputs.length
		puts inputs[0].length
		puts outputs.length
		puts outputs[0].length

		training_data = RubyFann::TrainData.new(
			:inputs=>inputs, 
			:desired_outputs=>outputs)

# Create FANN Neural Network to match appropriate training data:
		inputs = []
		outputs =[]

		0.upto(9) do |p|
			arr = Array.new
			inputs.push(arr)
			0.upto(299) do |i|
				arr.push(rand())
			end
			arr = Array.new
			arr.push(rand())
			outputs.push(arr)
		end



# Training using data created above:
		@fann.train_on_data(training_data, 1000, 1, 0.001)

# Run with different input data:

		outputs = @fann.run(inputs[0])[0]*100
		puts outputs
	end
end

f = Fann.new
f.run
