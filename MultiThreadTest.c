#include <stdio.h>
#include <pthread.h>

void* thread1( void* pParam );
void* thread2( void* pParam );
int count1 = 0;
int count2 = 0;
pthread_mutex_t mutex;

int main( void )
{
	pthread_t tid1, tid2;
	pthread_mutex_init( &mutex, NULL );

	pthread_create( &tid1, NULL, thread1, NULL );
	pthread_create( &tid2, NULL, thread2, NULL );

	pthread_join( tid1, NULL );
	pthread_join( tid2, NULL );

	pthread_mutex_destroy( &mutex );

	return 0;
}


void* thread1( void* pParam )
{
	int i;
	while( 1 )
	{
		printf( "Here is thread1.\n" );
		
		pthread_mutex_lock( &mutex );
		printf( "count1:" );
		for( i = 0; i < 10; i++ )
		{
			printf( "%d:", count1 );
			count1++;
		}

		printf( "\n" );
		sleep( 1 );
		pthread_mutex_unlock( &mutex );

		printf( "count2:" );
		for( i = 0; i < 10; i++ )
		{
			printf( "%d:", count2 );
			count2++;
		}
		printf( "\n" );
		sleep( 1 );
	}
}

void* thread2( void* pParam )
{
	int i;
	
	while( 1 )
	{
		printf( "Here is thread2.\n" );
		
		pthread_mutex_lock( &mutex );
		count1 = 0;
		sleep( 1 );
		pthread_mutex_unlock( &mutex );

		count2 = 0;
		sleep( 1 );
	}
}
