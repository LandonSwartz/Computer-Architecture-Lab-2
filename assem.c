#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 
#include <stdint.h> 
#include <assert.h>  
#include "assem.h"


uint32_t getr(char * given);

void main(int argc, char *argv[]) {

	FILE * fp; 	
	int i=0;
	int j=0;
	char *inst_arr[100000];

	for(int l =0; l<100000; l++)
	{
		inst_arr[l] = malloc(sizeof(char)*10000);
		
	}
	
	/* Open program file. */
	fp = fopen(argv[1], "r"); 
		
		if (fp == NULL) { 		
			printf("Error: Can't open program file %s\n", prog_file); 
			exit(-1); 
		}


		/* Read in the program into array of instructions. */ 



		while( fgets(inst_arr[i],100,(FILE*)fp) != NULL) 
		{	
			//printf("inst_array'i'=: %s", inst_arr[i]);
			i++;
			
		}
		 
			

		//printf("\n\n");
		uint32_t out[i];
		/*initialize output array*/

		for(j = 0; j < i; j++)
		{
			out[j] = 0x00000000;
		}

		for(j=0; j<i; j++)
		{
		//	printf("HERE\n");
			out[j] = gen_hex(inst_arr[j]);
		}

		
	fclose(fp);


	FILE *fp2;
	fp2 = fopen("output.txt", "w");
	if(fp2 == NULL)
	{
		printf("ayo file dne\n");
	}
	else
	{
		for(int q=0; q<i; q++)
		{
			fprintf(fp2,"%08X\n", out[q]); //08 prefix to always make 8 char hex number (in case of special instructions with functions and what not)

		}
		printf("ayo output file created\n");


	}

	
}

uint32_t gen_hex(char* inst){

	char op[100] = {0};
	char p1[100] = {0};
	char p2[100] = {0};
	char p3[100] = {0};
	int i = 0;
	int j = 0;

	uint32_t rvalue = 0x00000000;


	uint32_t p1hex; 
	uint32_t p2hex;
	uint32_t p3hex;
	uint32_t temp = 0;

	

	if(  (strcmp(inst, "syscall\n"))==0)
	{
		rvalue = 0xC;

		return rvalue;
		
		
	}
	else
	{

	while(inst[i] != ' '){
	
		op[i] = inst[i];
		i++;

	}

	i++;




	while(inst[i] != ' ' && inst[i] != NULL)
	{
		if(inst[i] == ',')
		{
			i++;
		}
		else if(inst[i] == '$')
		{
			i++;		
		}
		else
		{

			p1[j] = inst[i];
			i++;
			j++;
		}
	}

	i++;
	j = 0;
	
	while(inst[i] != ' '&& inst[i] != NULL)
	{
				
		if(inst[i] == ',')
		{
			i++;
		}
		else if(inst[i] == '$')
		{
			i++;
		}
		else
		{	
			p2[j] = inst[i];
			i++;
			j++;
		}
	}
	i++;
	j = 0;
	
	while(inst[i] != '\n' && inst[i] != NULL)
	{
		if(inst[i] == ',')
		{
			p3[j] = ' ';
		}
		else if(inst[i] == '$')
		{

			i++;
		}
		else
		{
				
			p3[j] = inst[i];
			i++;
			j++;
			//printf("p3[j] is: %c", p3[j]);
		}
	}


	p1hex = getr(p1);
	p2hex = getr(p2);
	p3hex = getr(p3);


	
		if(strcmp(op, "addiu") == 0)
		{

			rvalue = rvalue | (0b001001 << 26);
			//printf("Rvale is : %x", rvalue);

			temp =p1hex << 16;
			//printf("\n\ncurrnt temp: %x\n\n", temp);		
			rvalue = rvalue | temp;

			temp = p2hex << 21;
			//printf("\n\ncurrnt temp: %x\n\n", temp);	
			rvalue = rvalue | temp;
	
			temp = p3hex; 
			//printf("\n\ncurrnt temp: %x\n\n", temp);	
			rvalue = rvalue | temp;
			//printf("\n\ncurrnt rval: %X\n\n", rvalue);		
		}
		else if(strcmp(op,"addu") ==0)
		{
			rvalue = rvalue | (0b000000 << 26);
			temp = p2hex <<21;

			rvalue = rvalue | temp;
			temp = p3hex <<16;

			rvalue = rvalue | temp;
			temp = p1hex <<11;

			rvalue = rvalue | temp;
			rvalue = rvalue | 0b00000100001;
		}
		else if(strcmp(op, "addi") ==0)
		{
			
			rvalue = rvalue | (0b001000 << 26); //opcode
		
			temp =p1hex << 16; //rs
			
			rvalue = rvalue | temp;

			temp = p2hex << 21; //rt
		
			rvalue = rvalue | temp;
	
			temp = p3hex; 
		
			rvalue = rvalue | temp;
			
			printf("rvalue of addi is = %x\n", rvalue);
		
		}
		else if(strcmp(op,"add") ==0)
		{
			//printf("\nRvalue1: %x\n", rvalue);
			rvalue = rvalue | (0b000000 << 26);
			temp = p2hex <<21;
			//printf("\nRvalue2: %x\n", rvalue);

			rvalue = rvalue | temp;
			//printf("p3hex is %x", p3hex);
			temp = p3hex <<16;
			
			//printf("\nRvalue3: %x\n", rvalue);

			rvalue = rvalue | temp;
			//printf("\nRvalue3.5: %x\n", rvalue);
			temp = p1hex <<11;
			//printf("\nRvalue4: %x\n", rvalue);

			rvalue = rvalue | temp;
			rvalue = rvalue | 0b100000;
			//printf("\nRvalue5: %x\n", rvalue);
	
				
		}
		else if(strcmp(op, "sub") ==0)
		{
			rvalue = rvalue | (0b000000 << 26);
		
			temp = p1hex <<11;
			rvalue = rvalue | temp;

			temp = p2hex <<21;
			rvalue = rvalue | temp;
			
			temp = p3hex<<16;
			rvalue = rvalue | temp;
			rvalue = rvalue | 0b100010;

		}
		else if(strcmp(op, "subu") ==0)
		{
			rvalue = rvalue | (0b000000 << 26);
		
			temp = p1hex <<11;
			rvalue = rvalue | temp;

			temp = p2hex <<21;
			rvalue = rvalue | temp;
			
			temp = p3hex<<16;
			rvalue = rvalue | temp;
			rvalue = rvalue | 0b100011;
		}
		else if(strcmp(op,"mult") ==0)
		{
			rvalue = rvalue | (0b000000 << 26);
		
			temp = p1hex <<21;
			rvalue = rvalue | temp;

			temp = p2hex<<16;
			rvalue = rvalue | temp;
			
			rvalue = rvalue | 0b011000;
		}
		else if(strcmp(op, "multu") ==0)
		{
			rvalue = rvalue | (0b000000 << 26);
		
			temp = p1hex <<21;
			rvalue = rvalue | temp;

			temp = p2hex<<16;
			rvalue = rvalue | temp;
			
			rvalue = rvalue | 0b011001;

		}
		else if(strcmp(op,"div") ==0)
		{
			rvalue = rvalue | (0b000000 << 26);
		
			temp = p1hex <<21;
			rvalue = rvalue | temp;

			temp = p2hex <<16;
			rvalue = rvalue | temp;
				
			rvalue = rvalue | 0b011010;

		}
		else if(strcmp(op, "divu") ==0)
		{
			rvalue = rvalue | (0b000000 << 26);
		
			temp = p1hex <<21;
			rvalue = rvalue | temp;

			temp = p2hex <<16;
			rvalue = rvalue | temp;
			
			rvalue = rvalue | 0b011011;

		}
		else if(strcmp(op, "and") ==0)
		{
			rvalue = rvalue | (0b000000 << 26);
			temp = p2hex <<21;

			rvalue = rvalue | temp;
			temp = p3hex <<16;

			rvalue = rvalue | temp;
			temp = p1hex <<11;

			rvalue = rvalue | temp;
			rvalue = rvalue | 0b00000100100;
			

		}
		else if(strcmp(op, "andi") ==0)
		{
			rvalue = rvalue | (0b001100 << 26);
			temp = p2hex <<21;

			rvalue = rvalue | temp;
			temp = p3hex;

			rvalue = rvalue | temp;
			temp = p1hex <<16;

			rvalue = rvalue | temp;
		}
		else if(strcmp(op, "or") ==0)
		{	
			rvalue = rvalue | (0b000000 << 26);
		
			temp = p1hex <<11;
			rvalue = rvalue | temp;

			temp = p2hex<<21;
			rvalue = rvalue | temp;
			
			temp = p3hex<<16;
			rvalue = rvalue | temp;

			rvalue = rvalue | 0b100101;		
		}
		else if(strcmp(op, "ori") ==0)
		{
			rvalue = rvalue | (0b000000 << 26);
		
			temp = p1hex <<16;
			rvalue = rvalue | temp;

			temp = p2hex<<21;
			rvalue = rvalue | temp;
			
			temp = p3hex;
			rvalue = rvalue | temp;

		}
		else if(strcmp(op, "xor") ==0)
		{
			rvalue = rvalue | (0b000000 << 26);
		
			temp = p1hex <<11;
			rvalue = rvalue | temp;

			temp = p2hex <<21;
			rvalue = rvalue | temp;
			
			temp = p3hex<<16;
			rvalue = rvalue | temp;
			rvalue = rvalue | 0b100110;
		}
		else if(strcmp(op, "nor") ==0)
		{
			rvalue = rvalue | (0b000000 << 26);
		
			temp = p1hex <<11;
			rvalue = rvalue | temp;

			temp = p2hex<<21;
			rvalue = rvalue | temp;
			
			temp = p3hex<<16;
			rvalue = rvalue | temp;

			rvalue = rvalue | 0b100111;		
		}
		else if(strcmp(op, "slt") ==0)
		{
			rvalue = rvalue | (0b000000 << 26);
			temp = p2hex <<21;

			rvalue = rvalue | temp;
			temp = p3hex <<16;

			rvalue = rvalue | temp;
			temp = p1hex <<11;

			rvalue = rvalue | temp;
			rvalue = rvalue | 0b101010;

		}
		else if(strcmp(op, "slti") ==0)
		{
			rvalue = rvalue | (0b001010 << 26);
			temp = p2hex <<21;

			rvalue = rvalue | temp;
			temp = p3hex;

			rvalue = rvalue | temp;
			temp = p1hex <<16;

			rvalue = rvalue | temp;

		}
		else if(strcmp(op, "sll") ==0)
		{
			rvalue = rvalue | (0b000000 << 26);
			temp = p2hex <<16;

			rvalue = rvalue | temp;
			temp = p3hex<<6;

			rvalue = rvalue | temp;
			temp = p1hex <<11;

			rvalue = rvalue | temp;

		}
		else if(strcmp(op, "srl") ==0)
		{
			rvalue = rvalue | (0b000000 << 26);
			temp = p2hex <<16;

			rvalue = rvalue | temp;
			temp = p3hex<<6;

			rvalue = rvalue | temp;
			temp = p1hex <<11;

			rvalue = rvalue | temp;
			rvalue = rvalue | 0b000010;
		}
		else if(strcmp(op, "sra") ==0)
		{
			rvalue = rvalue | (0b000000 << 26);
			temp = p2hex <<16;

			rvalue = rvalue | temp;
			temp = p3hex<<6;

			rvalue = rvalue | temp;
			temp = p1hex <<11;

			rvalue = rvalue | temp;
			rvalue = rvalue | 0b000011;
		}
		else if(strcmp(op, "lw") ==0)
		{
			rvalue = rvalue | (0b100011 << 26);
		
			temp = p1hex <<16;
			rvalue = rvalue | temp;

			temp = p2hex;
			rvalue = rvalue | temp;
			
			temp = p3hex<<21;
			rvalue = rvalue | temp;		
		}
		else if(strcmp(op, "lb") ==0)
		{
			rvalue = rvalue | (0b100000 << 26);
		
			temp = p1hex <<16;
			rvalue = rvalue | temp;

			temp = p2hex;
			rvalue = rvalue | temp;
			
			temp = p3hex<<21;
			rvalue = rvalue | temp;
		}
		else if(strcmp(op, "lh") ==0)
		{
			rvalue = rvalue | (0b100001 << 26);
		
			temp = p1hex <<16;
			rvalue = rvalue | temp;

			temp = p2hex;
			rvalue = rvalue | temp;
			
			temp = p3hex<<21;
			rvalue = rvalue | temp;
		}
		else if(strcmp(op, "lui") ==0)
		{
			rvalue = rvalue | (0b001111 << 26);
		
			temp = p1hex <<16;
			rvalue = rvalue | temp;

			temp = p2hex;
			rvalue = rvalue | temp;
			
		}
		else if(strcmp(op, "sw") ==0)
		{
			rvalue = rvalue | (0b101011 << 26);
		
			temp = p1hex <<16;
			rvalue = rvalue | temp;

			temp = p2hex;
			rvalue = rvalue | temp;
			
			temp = p3hex<<21;
			rvalue = rvalue | temp;
		}
		else if(strcmp(op, "sb") ==0)
		{
			rvalue = rvalue | (0b101000 << 26);
		
			temp = p1hex <<16;
			rvalue = rvalue | temp;

			temp = p2hex;
			rvalue = rvalue | temp;
			
			temp = p3hex<<21;
			rvalue = rvalue | temp;
		}
		else if(strcmp(op, "sh") ==0)
		{
			rvalue = rvalue | (0b101001 << 26);
		
			temp = p1hex <<16;
			rvalue = rvalue | temp;

			temp = p2hex;
			rvalue = rvalue | temp;
			
			temp = p3hex<<21;
			rvalue = rvalue | temp;
		}
		else if(strcmp(op, "mfhi") ==0)
		{
			rvalue = rvalue | (0b000000 << 26);
		
			temp = p1hex <<16;
			rvalue = rvalue | temp;
	
			rvalue = rvalue | 0b010000;
		}
		
		else if(strcmp(op, "mflo") ==0)
		{
			rvalue = rvalue | (0b000000 << 26);
		
			temp = p1hex <<16;
			rvalue = rvalue | temp;
	
			rvalue = rvalue | 0b010010;
		}
		else if(strcmp(op, "mthi") ==0)
		{
			rvalue = rvalue | (0b000000 << 26);
		
			temp = p1hex <<21;
			rvalue = rvalue | temp;
	
			rvalue = rvalue | 0b010001;
		}
		else if(strcmp(op, "mtlo") ==0)
		{
			rvalue = rvalue | (0b000000 << 26);
		
			temp = p1hex <<21;
			rvalue = rvalue | temp;
	
			rvalue = rvalue | 0b010011;

		}
		else if(strcmp(op, "beq") ==0)
		{
			rvalue = rvalue | (0b000100 << 26);
		
			temp = p1hex <<21;
			rvalue = rvalue | temp;

			temp = p2hex <<16;
			rvalue = rvalue | temp;
			
			temp = p3hex;
			rvalue = rvalue | temp;
		}
		else if(strcmp(op, "bne") ==0)
		{
			rvalue = rvalue | (0b000101 << 26);
		
			temp = p1hex <<21;
			rvalue = rvalue | temp;

			temp = p2hex <<16;
			rvalue = rvalue | temp;
		
			printf("p3 is: %x", p3hex);

			temp = p3hex;
			rvalue = rvalue | temp;
				
		}
		else if(strcmp(op, "blez") ==0)
		{
			rvalue = rvalue | (0b000110 << 26);
		
			temp = p1hex <<21;
			rvalue = rvalue | temp;

			temp = p2hex;
			rvalue = rvalue | temp;
			
		}
		else if(strcmp(op, "bltz") ==0)
		{
			rvalue = rvalue | (0b000001 << 26);
		
			temp = p1hex <<21;
			rvalue = rvalue | temp;

			temp = p2hex;
			rvalue = rvalue | temp;
			
		}
		else if(strcmp(op, "bgez") ==0)
		{
			rvalue = rvalue | (0b000001 << 26);
		
			temp = p1hex <<21;
			rvalue = rvalue | temp;

			temp = p2hex;
			rvalue = rvalue | temp;

			rvalue = rvalue | 0b00001 <<16;
		}
		else if(strcmp(op, "j") ==0)
		{
			rvalue = rvalue | (0b000010 << 26);
		
			temp = p1hex;
			rvalue = rvalue | temp;

		}
		else if(strcmp(op, "jr") ==0)
		{
			rvalue = rvalue | (0b000000 << 26);
		
			temp = p1hex<<21;
			rvalue = rvalue | temp;

			rvalue = rvalue | 0b001000;
	
		}
		else if(strcmp(op, "jal") ==0)
		{
			rvalue = rvalue | (0b000011 << 26);
		
			temp = p1hex;
			rvalue = rvalue | temp;

		}
		else if(strcmp(op, "jalr") ==0)
		{
			rvalue = rvalue | (0b000000 << 26);
		
			temp = p1hex<<11;
			rvalue = rvalue | temp;
			
			temp = p2hex<<21;
			rvalue = rvalue | temp;

			rvalue = rvalue | 0b001001;
			

		}
		else
		{
			printf("No instruction found...\n");
				//didn't find an instruction for it
		}
		
	}
	
	//printf("rvalue = %x\n", rvalue);
	return rvalue;
}


uint32_t getr(char * given)
{


	uint32_t holder;

	if((given[0]== 'f' || given[0] == '-'))	
	{
	
	//	printf("\n%x here", strtol(given,NULL,16));
		holder = (strtol(given, NULL, 16));
		return (uint32_t*) holder;
	}
	else if(given[0] == '0')
	{
	
	
	//	printf("\n%x here", strtol(given,NULL,16));
		given[1] = '0';
		holder = (uint32_t*)(strtol(given, NULL, 16));
		return (uint32_t*) holder;
		}

	else if(strcmp(given, "zero") ==0)
	{
		return 0x0;
	}
	else if(strcmp(given, "at") ==0)
	{
		return 0x1;

	}
	else if(strcmp(given, "v0") ==0)
	{
		return 0x2;

	}
	else if(strcmp(given, "v1") ==0)
	{
		return 0x3;

	}
	else if(strcmp(given, "a0") ==0)
	{
		return 0x4;

	}
	else if(strcmp(given, "a1") ==0)
	{
		return 0x5;

	}
	else if(strcmp(given, "a2") ==0)
	{
		return 0x6;

	}
	else if(strcmp(given, "a3") ==0)
	{
		return 0x7;

	}
	else if(strcmp(given, "t0") ==0)
	{
		return 0x8;

	}
	else if(strcmp(given, "t1") ==0)
	{
		return 0x9;

	}
	else if(strcmp(given, "t2") ==0)
	{
		return 0xA;

	}
	else if(strcmp(given, "t3") ==0)
	{
		return 0xB;

	}
	else if(strcmp(given, "t4") ==0)
	{
		return 0xC;

	}
	else if(strcmp(given, "t5") ==0)
	{
		return 0xD;

	}
	else if(strcmp(given, "t6") ==0)
	{
		return 0xE;

	}		
	else if(strcmp(given, "t7") ==0)
	{
		return 0xF;

	}
	else if(strcmp(given, "s0") ==0)
	{
		return 0x10;

	}
	else if(strcmp(given, "s1") ==0)
	{
		return 0x11;

	}
	else if(strcmp(given, "s2") ==0)
	{
		return 0x12;

	}
	else if(strcmp(given, "s3") ==0)
	{
		return 0x13;

	}

	else if(strcmp(given, "s4") ==0)
	{
		return 0x14;

	}
	else if(strcmp(given, "s5") ==0)
	{
		return 0x15;

	}
	else if(strcmp(given, "s6") ==0)
	{
		return 0x16;

	}
	else if(strcmp(given, "s7") ==0)
	{
		return 0x17;

	}
	else if(strcmp(given, "t8") ==0)
	{
		return 0x18;

	}
	else if(strcmp(given, "t9") ==0)
	{
		return 0x19;

	}
	else if(strcmp(given, "k0") ==0)
	{
		return 0x1A;

	}
	else if(strcmp(given, "k1") ==0)
	{
		return 0x1B;

	}
	else if(strcmp(given, "gp") ==0)
	{
		return 0x1C;

	}
	else if(strcmp(given, "sp") ==0)
	{
		return 0x1D;

	}
	else if(strcmp(given, "fp") ==0)
	{
		return 0x1E;

	}
	
	else if(strcmp(given, "ra") ==0)
	{
		return 0x1F;

	}
	if((given == 'f') || (given == '0'))
	{
		return strtol(given, NULL, 16);
	}
}
