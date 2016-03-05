#include <stdio.h>  
#include <pthread.h> 
#include <unistd.h> 
  
#define Read_Num 2  
  
pthread_rwlock_t lock;  
  
class Data  
{  
    public:  
        Data(int i, float f): I(i),F(f)  
            {}  
        int I;  
        float F;  
              
};  
  
Data *pdata = NULL;  
  
  
void *read(void * arg)  
{  
    int id = *(int*)arg;  
    while(true)  
        {  
      
            pthread_rwlock_rdlock(&lock);  
            printf(" reader %d is reading data!\n", id);  
            if(pdata == NULL)  
                {  
                    printf("data is NULL\n");  
                }  
            else  
                {  
                    printf("data: I = %d, F = %f \n", pdata->I, pdata->F);  
                }  
                pthread_rwlock_unlock(&lock);  
        }  
      
    pthread_exit(0);  
      
}  
  
void *write(void * arg)  
{  
    while(true)  
        {  
            pthread_rwlock_wrlock(&lock);  
            printf(" writer is writind data!\n");  
            if(pdata == NULL)  
                {  
                    pdata = new Data(1, 1.1);  
                    printf("Writer is writing data: %d, %f\n", pdata->I, pdata->F);  
                }  
            else  
                {  
                    delete pdata;  
                    pdata = NULL;  
                    printf("writer free the data!");  
                }  
  
            pthread_rwlock_unlock(&lock);  
        }  
    pthread_exit(0);  
}  

    int  main()  
    {  
        pthread_t reader[Read_Num];  
        pthread_t writer;  
      
        for(int i = 0;i<Read_Num;i++)  
            {  
                pthread_create(&reader[i],NULL,read,(void *)&i);  
            }  
        //pthread_create
        pthread_create(&writer, NULL, write, NULL);  
      
        sleep(1);  
        return 0;  
    }  
