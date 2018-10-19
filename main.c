/*ARCHTRAIN by RooMan*/
/*Version 0.1.1*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <main.h>
#include <libgen.h>
#define _GNU_SOURCE
#pragma (pack 0)

typedef struct{
	unsigned short headerMagic;//magic number
	unsigned short headerBlocks;//total blocks(files)
	unsigned int headerFileSize;//total file size
}ARCHIVE_HEADER;//structure for the header

typedef struct{
	char blockName[12];//file name
	unsigned int blockSize;//size of input file
}ARCHIVE_BLOCK;//structure to hold block infomation

int main (int argc, char** argv){
	ARCHIVE_HEADER head;//create header
	FILE *fp,*tp;//file stream and temp filestream
	int i,j,tempFileSize,MAX_BLOCKS=argc-2;
	char tempByte,*tempBase; //temp byte to copy and temp basename(file name)
	ARCHIVE_BLOCK blocks[MAX_BLOCKS];//ARCHIVE_BLOCK for each input file argument

	if(argc<=2){//catch error: too few arguments
		printf("usage: [input file(s)] [outputfile]\n");
		return(1);
	}
	fp=fopen(argv[argc-1],"w+b");//open the last argument filename(output)
	head.headerMagic=(0x5443);//set magic number 
	head.headerFileSize=(sizeof(ARCHIVE_HEADER) + 
		(sizeof(ARCHIVE_BLOCK)*MAX_BLOCKS) );//calculate size of header
	head.headerBlocks=(MAX_BLOCKS);//set total number of blocks (files)
	fwrite(&head,sizeof(ARCHIVE_HEADER),1,fp);//write header
	for(j=1;j<argc-1;j++){//open files from input arguments
		tp=fopen(argv[j],"r+b");//open input file
		if(!tp){//catch error: unreadable file
			continue;//skip unreadable files
		}
		printf("writting %s\n",argv[j]);//begin writing block
		tempBase=basename(argv[j]);//find the filename
		memset(blocks[j-1].blockName,'\0',12);//erase the any data at this address
		strcpy(blocks[j-1].blockName, tempBase);//write the filename to this address
		fseek(tp,0,SEEK_END);//find the size of the input file
		blocks[j-1].blockSize=ftell(tp);//update the block file size
		head.headerFileSize+=blocks[j-1].blockSize;//update the total filesize
		fseek(tp,0,SEEK_SET);//jump back
		fwrite(&blocks[j-1],sizeof(ARCHIVE_BLOCK),1,fp);//write the block
		for(i=0;i<blocks[j-1].blockSize;i++){//copy the input file
			fread(&tempByte,1,1,tp);
			fwrite(&tempByte,1,1,fp);
		}
		fclose(tp);//close this input file
	}
	fseek(fp,4,SEEK_SET);//jump to this spot in the header (filesize)
	fwrite(&head.headerFileSize,sizeof(head.headerFileSize),1,fp);//write the new filesize
	fclose(fp);//close output file

return 0;//bye
}


