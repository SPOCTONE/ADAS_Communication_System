all: menu.o CASinput.o CASalert.o LDW.o ACCsend.o ACCreceive.o AEBclient.o AEBserver.o CASclient.o CASserver.o BSDinput.o BSDalert.o

	gcc menu.o -o menu
	gcc CASinput.o -o CAS
	gcc CASalert.o -o CASalert
	gcc CASclient.o -o CASclient
	gcc CASserver.o -o CASserver
	gcc LDW.o -o LDW
	gcc ACCsend.o -o ACCsend
	gcc ACCreceive.o -o ACCreceive
	gcc AEBclient.o -o AEBclient
	gcc AEBserver.o -o AEBserver
	gcc BSDinput.o -o BSD
	gcc BSDalert.o -o BSDalert
	./menu

menu.o: menu.c
        gcc -c menu.c

CASinput.o: CASinput.c	
            gcc -c CASinput.c

CASalert.o: CASalert.c
	    gcc -c CASalert.c 

CASclient.o: CASclient.c
             gcc -c CASclient.c

CASserver.o: CASserver.c 
             gcc -c CASserver.c

LDW.o:  LDW.c
        gcc -c LDW.c 

ACCsend.o: ACCsend.c
           gcc -c ACCsend.c

ACCreceive.o: ACCreceive.c
              gcc -c ACCreceive.c

AEBclient.o: AEBclient.c
             gcc -c AEBclient.c

AEBserver.o: AEBserver.c 
             gcc -c AEBserver.c

BSDinput.o: BSDinput.c 
       gcc -c BSDinput.c

BSDalert.o: BSDalert.c
            gcc -c BSDalert.c

clean:
	rm *.o
