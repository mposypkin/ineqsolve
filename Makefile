all dep clean indent tests::
	cd unigrid && $(MAKE) $@ && cd .. 
	
clean::
	rm -rf *~ PI* core bin/* obj/* tmp *.log
