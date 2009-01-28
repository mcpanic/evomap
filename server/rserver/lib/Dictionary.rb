class Dictionary

	@@_words = <<-EOF
a
b
c
d
e
f
g
h
j
k
l
EOF
	@@__words = <<-EOF
1. Music

A cappella
Accent
Articulation
Attack
Breath
Chord
Chromatic
Compound meter
Counting
Diatonic
Diction
Dipthong
Dynamics
Embouchure
Harmony
Homophonic
Intonation
Key--major
Key--minor
Melody
Meter
Phrase
Pitch
Placement
Polyphonic
Posture
Pulse
Release
Rhythm
Sacred 
Secular
Slur
Solfege
Tempo
Tone color/Timbre
Tongue
Unison


2. Earth Science
air current
atmosphere
barometer
cellular respiration
conduction
convection
matter
mesosphere
monsoon
newton
pressure
radiant energy
radiation
stratosphere
thermosphere
troposphere
wind
air mass
capacity
cirrus cloud
cold front
condensation
cumulus cloud
dew point
evaporation
front
frost
hurricane
polar air mass
precipitation
rain guage
saturated
specific humidity
stratus cloud
thunderstorm
tornado
transpiration
tropical air mass
warm front
alititude
biome
climate 
latitude
microclimate
middle-latitude zone
polar zone
vegetation
weather
axis
equinox
International Date Line
revolution
rotation
solar noon
solstice
acid rain
conservation
environment
hydroelectric power
litter
natural resource
nuclear energy
pollutant
pollution
sewage
smog
astronomical unit
astronomy
galaxy
light year
parallax
satellite
solar system
asteroid
comet
crater
ellipse
mare 
meteor
meteorite
meteoroid
nebula
orbit
rift
Big Bang
black hole
chromosphere
constellation
core
corona
elliptical galaxy
fusion
irregular galaxy
magnitude
main sequence star
nova
nucleus
photosphere
prominence
protostar
quasar
red giant
solar flare
spectrograph
spetroscopy
spectrum
spiral galaxy
star
star cluster
sunspot
supergiant
supernova
white dwarf


3. Life Science

Behavior
Flat Teeth
Genes
Generations
Genetics
Heredity
Inherited Trait
Instinct
Learned/Acquired Behavior
Sharp Teeth
Carnivore
Competition
Consumed
Decomposer
Habitat
Herbivore
Niche
Omnivore
Predator
Prey
Primary Consumer
Producer
Scavenger
Secondary Consumer
Adaptation
Advantage
Biome
Body Covering
Camouflage
Characteristic / Trait
Diversity
Ecosystem
Extinct
Food Chain
Food Web
Hibernation
Interaction
Adult
Chrysalis
Community
Complete Metamorphosis
Direct Development
Egg
Incomplete Metamorphosis
Larva
Metamorphosis
Nymph
Pupa
Development
Environment
Germination
Leaf
Life Cycle
Nutrient
Offspring
Organism
Reproduction
Resource
Seed
Species
Survive
Vegetation

1. Economy
economic institution
small firm
large firm
labor union
not-for-profit organization
economic conditions
economic incentive
labor force
command economy
traditional economy
market economy
relative price
purchase decision
sales decision
advertising
collusion
competition
market
market size
tacit
overt
productivity
incentive
innovation
investment
research and development
physical capital
human capital
monopoly
oligopoly
perfect competition
interest rate
mortgage rates
interest points
prime rate
Federal Reserve
real interest rate
nominal interest rate
current interest rate
expected rate of inflation
inflation
incentive
budget
CD's
TSA's
401K
mutual funds


2. Politics

federalism
sovereignty
ratification
social contract
faction
Preamble
Bill of Rights
amendment
parameters
order
predictability
security
conflict management
economic relationship
social relationship
civil society
source of law
sovereign
legislature
divine law
natural law
common law
statute law
international law
Supreme Being
individual rights
freedom of religion
freedom of expression
discrimination
common good
congressional act
committee review
lobbying
limited government
Magna Carta
English Bill of Rights
Articles of Confederation
Bill of Rights
Two Treatises of Government
social contract
Leviathan
power of the purse

power of impeachment
advice and consent
veto power
judicial review
separation of powers
individual rights
judicial process
constitutional law
criminal law
civil law
appellate
respondent
guarantor
district
state
circuit
federal court
distribution of power
shared power
limited power
confederal system of government
federal system of government
unitary system of government
popular will
abuse of power
powers of the states
interstate commerce
Fourteenth Amendment
Tenth Amendment
intrastate

EOF
		
	@@ready = false

	def self.ready
		unless @@ready
			@@ready = true
			@@words = @@_words.split("\n").delete_if do |x|
				not (x =~ /^[A-Za-z]+/)
			end
		end
	end

	def ready
		unless @@ready
			@@ready = true
			@@words = @@_words.split("\n").delete_if do |x|
				not (x =~ /^[A-Za-z]+/)
			end
		end
	end


	def initialize
		ready
	end	

	def self.lookup(id)
		ready
   	@@words[id.to_i]
	end

	def self.size
		ready
		@@words.length
	end

	def lookup(id)
		ready
		@@words[id.to_i]
	end	
	
end
