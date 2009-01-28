require 'rubygems'
require 'Dictionary'
require 'ruby_fann/neural_network'

class NN

	def initialize
		@fann = RubyFann::Standard.new(
			:num_inputs=>Dictionary.size, 
			:hidden_neurons=>[10, 10, 10, 10], 
			:num_outputs=>1)
	end

	def train(graph, score)
		inputs = [graph2inputs(graph)]
		outputs = [[score.to_f/100]]
			training_data = RubyFann::TrainData.new(
			:inputs=>inputs, 
			:desired_outputs=>outputs)
	
		@fann.train_on_data(training_data, 30, 0, 0.001)
	end

	def eval(graph)
		inputs = graph2inputs(graph)
		outputs = @fann.run(inputs)
		(outputs[0]*100).to_i
	end

#private

	def graph2inputs(graph)
		inputs = Array.new(Dictionary.size,0.0)
		graph.each do |k,v|
			inputs[k.to_i] = v.size.to_f / Dictionary.size
		end
		inputs
	end

end
