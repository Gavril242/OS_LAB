#include <stdio.h>
#include <stdlib.h>

printmenuL(struct stat lucian){

    printf("This file is a link, please select oone of the following arguments:
    \n-n(filename)\n-l(delete link)\n-d(size of the link)\n-t(size of the target)\n-a(acces rights)\nYour imput command:");

}

printmenuR(struct stat lucian){
        printf("This file is a file, please select oone of the following arguments:
    \n-n(filename)\n-l(delete link)\n-d(size of the link)\n-t(size of the target)\n-a(acces rights)\nYour imput command:");


}

int main(int argc, char * argv[]){

    

    if(argc<1){perror("No arguments added"); exit(1);}

    struct stat lucian; 

    for(int i=1; i< argc; i++){
       
        printf(" %s\n",argv[i]);
        if(lstat(argv[i],&lucian)){perror("argument is not a file/direcorty/link soly");exit(1);}
        if(S_ISREG(lucian.st_mode)){ printmenuR(lucian);  }
        if(S_ISLNK(lucian.st_mode)){ printmenuL(lucian);  }
      
    } 

    return 0;
}