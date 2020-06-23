struct flock c;
c.l_type = 
c.l_whence = SEEK_SET;
c.l_start = 0;
c.l_len = 0;
int fd;

for(int i=1; i< argc; i++){
	fd = open(argv[i]);
	//error

	// poner cerrojo de escritura con espera
	if(errno== EDEADLK)
		
}