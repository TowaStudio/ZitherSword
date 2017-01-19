/*
  ==============================================================================

    SeqIdentify.h
    Created: 19 Jan 2017 1:29:23pm
    Author:  SDUser

  ==============================================================================
*/

#ifndef SEQIDENTIFY_H_INCLUDED
#define SEQIDENTIFY_H_INCLUDED

class SeqIdentify{
    
public:  
    int seqInput[16]; 

	SeqIdentify(int[]) {};
	SeqIdentify() {};
	~SeqIdentify() {};
    
public: 
	int identify();
	int result();
    
};

#endif  // SEQIDENTIFY_H_INCLUDED
