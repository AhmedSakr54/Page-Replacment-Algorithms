lab4: lab4.cc
	g++ lab4.cc -o lab4
	cat inputOPTIMAL.txt | ./lab4 | diff outputOPTIMAL.txt -
	cat inputCLOCK.txt | ./lab4 | diff outputCLOCK.txt -
	cat inputLRU.txt | ./lab4 | diff outputLRU.txt -
	cat inputFIFO.txt | ./lab4 | diff outputFIFO.txt -