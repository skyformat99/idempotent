#include "idempotent/idempotent.h"
#include <pthread.h>
#include <unistd.h>
#include <iostream>
using namespace std;
#define NUM_THREADS 50
std::string json_str = "{\"cache\":{\"slice\":[[{\"key\":0,\"role\":0,\"host\":\"127.0.0.1\",\"port\":6379,\"pwd\":\"\",\"conn_timeout\":10,\"min_conn_count\":2,\"max_conn_count\":10},{\"key\":0,\"role\":1,\"host\":\"127.0.0.1\",\"port\":6379,\"pwd\":\"\",\"conn_timeout\":10,\"min_conn_count\":2,\"max_conn_count\":10}],[{\"key\":1,\"role\":0,\"host\":\"127.0.0.1\",\"port\":6379,\"pwd\":\"\",\"conn_timeout\":10,\"min_conn_count\":2,\"max_conn_count\":10},{\"key\":1,\"role\":1,\"host\":\"127.0.0.1\",\"port\":6379,\"pwd\":\"\",\"conn_timeout\":10,\"min_conn_count\":2,\"max_conn_count\":10}]]}} ";

void* consumer(void *t) {
    int start=0;
    int end=100000;

    Idempotent ide_ptr;
	ide_ptr.init(json_str);
    do {
        for (int idx = start; idx < end; ++idx) {
            char szKey[256] = {0};
            sprintf(szKey, "test_%d", idx);
            std::cout << "key:" << szKey << std::endl;
            bool ret = ide_ptr.can_handle("msg_id", szKey);
            if (ret) {
                printf("func:%s, key:%s\n", __FUNCTION__, szKey);
            } else {
                std::cout << "error func:" << __FUNCTION__
                    << ",key:" << szKey << std::endl;
            }
        }
        usleep(100);
    } while(0);

}

void* reconsumer(void *t) {
    int start=0;
    int end=100000;

    Idempotent ide_ptr;
    do {
        for (int idx = start; idx < end; ++idx) {
            char szKey[256] = {0};
            sprintf(szKey, "test_%d", idx);
            bool ret = ide_ptr.reset_handle("msg_id", szKey);
            if (ret) {
				std::cout << __FUNCTION__ << szKey << std::endl;
            } else {
                std::cout << "error func:" << __FUNCTION__
                    << ",key:" << szKey << std::endl;
            }
        }
        usleep(100);
    } while(0);
}


int main(int argc, char **argv) {
    //正常消费
    consumer(NULL);
    //重置消费
    //reconsumer(0, 10);
    //重置消费
    //reconsumer(0, 10);

    //// 定义线程的 id 变量，多个变量使用数组
    //pthread_t consumer_tids[NUM_THREADS];
    //for(int i = 0; i < NUM_THREADS; ++i) {
    //    //参数依次是：创建的线程id，线程参数，调用的函数，传入的函数参数
    //    int ret = pthread_create(&consumer_tids[i], NULL, consumer, (void*)NULL);
    //    if (ret != 0) {
    //        std::cout << "pthread_create error: error_code=" << ret << endl;
    //    }
    //}


    //// 定义线程的 id 变量，多个变量使用数组
    //pthread_t reconsumer_tids[NUM_THREADS];
    //for(int i = 0; i < NUM_THREADS; ++i) {
    //    //参数依次是：创建的线程id，线程参数，调用的函数，传入的函数参数
    //    int ret = pthread_create(&reconsumer_tids[i], NULL, reconsumer, (void*)NULL);
    //    if (ret != 0) {
    //        std::cout << "pthread_create error: error_code=" << ret << endl;
    //    }
    //}

    ////等各个线程退出后，进程才结束，否则进程强制结束了，线程可能还没反应过来；
    //pthread_exit(NULL);

    return 0;
}

