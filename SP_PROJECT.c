#include<stdio.h>
#include<sys/stat.h>
#include<dirent.h>
#include<fcntl.h>
#include<string.h>
#include<stdlib.h>
int is_regular_file(const char *path);
int main(int argc,char *argv[])
{
	int a=0;
    	char *buf,*buf1;
    	DIR *d;
    	struct dirent *dir;
    	struct stat s1;    
    	d = opendir(argv[2]);
    	int fd,status;
    	int bytesread;
    	int check;
    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
		//if(stat(dir->d_name,&s1)!=0)
		//{
		//	perror("ERROR ");
		//}					for displaying size of file
            //	printf("%s \n", dir->d_name);
	
	buf=(char *)malloc(sizeof(char)*100);
	buf1=(char *)malloc(sizeof(char)*100);
	int a=0,dots=0;
	for(a=0;a<100;a++)
	{
		buf1[a]='\0';
	}
	strcpy(buf1,dir->d_name);
	for(a=0;a<2;a++)
	{
	if((int)buf1[a]==46)
	{
		if(buf1[a+1]=='\0')
		{	
		dots=1;
		}
	}
	}
	//free(buf1);
	if(dots==1)
	{
		continue;
	}	
	strcat(buf,argv[2]);
	strcat(buf,"/");
	strcat(buf,dir->d_name);
	
	int file_type=is_regular_file(buf);
	if(file_type)
	{
	//	printf("Opening file : %s \n",buf);
	fd=open(buf,O_RDONLY|O_NONBLOCK);
	}
	else
	{
			char *argv1[]={"./test",argv[1],buf,NULL};
			main(3,argv1);
		//	if(buf!=NULL)
		//		{free(buf);}
			continue;
	}
	if(fd==-1)
	{
		perror("ERROR ");
	}
	char character_read;
	do
	{
		character_read='@';
		bytesread=read(fd,&character_read,1);
		int a=0;
		check=0;
		for(a=0;argv[1][a]!='\0';a++)
		{
			if(character_read==argv[1][a])
			{
				if(argv[1][a+1]=='\0' && check==1)
				{
				//printf("THE LAST ITEM \n");
				check=1;
				break;
				}
				check=1;
			}
			else
			{
				check=0;
				break;
			}
			character_read='@';
			bytesread=read(fd,&character_read,1);
		}
			if(check==1 && bytesread==1)
			{
				break;
			}
			else
			{
				check=0;
			}
//	free(buf);
	}
	while(character_read!='@');
	close(fd);
	 if(check==1)
        {
                printf("FILE : %s \n",buf);
        }	
        }
//	 if(check==1 && readdir(d)!=NULL)
//	{
//		printf("TRUE FILE : %s \n",dir->d_name);		
//	}
        closedir(d);
    }
	
}
int is_regular_file(const char *path)
{
    struct stat path_stat;
    stat(path, &path_stat);
    return S_ISREG(path_stat.st_mode);
}
