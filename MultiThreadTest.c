#include <stdio.h>
#include <pthread.h>

void* thread1( void* pParam );
void* thread2( void* pParam );
int count1 = 0;
int count2 = 0;
pthread_mutex_t mutex;

/*======================================================================*/

pthread_t Thread_create( void* (*start_routine)( void* ) )
{
	pthread_t tid;
	
	pthread_create( &tid, NULL, start_routine, NULL );
	return tid;
}

/*======================================================================*/

void Thread_waitUntilExit( pthread_t tid )
{
	pthread_join( tid, NULL );
}

/*======================================================================*/

int main( void )
{
	pthread_t tid1, tid2;
	pthread_mutex_init( &mutex, NULL );

	tid1 = Thread_create( thread1 );
	tid2 = Thread_create( thread2 );

	Thread_waitUntilExit( tid1 );
	Thread_waitUntilExit( tid2 );

	pthread_mutex_destroy( &mutex );

	return 0;
}

/*======================================================================*/

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

/*======================================================================*/

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
