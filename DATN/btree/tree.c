void search(BTA*tree, char *input, char **output){
	int size;
	*output = (char*)malloc(256*sizeof(char*));
	if(btsel(tree ,input,*output,256*sizeof(char),&size)!=0){
		free(*output);
		*output=NULL;
	}
}