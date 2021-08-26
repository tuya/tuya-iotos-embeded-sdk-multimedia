#include "tuya_hal_mutex.h"
#include "tuya_hal_thread.h"
#include "tuya_hal_semaphore.h"
#include "tuya_hal_wifi.h"
#include "tuya_hal_network.h"
#include "tuya_cloud_error_code.h"
#include "tuya_hal_memory.h"
#include "tuya_hal_system.h"
#include "tuya_hal_storge.h"

#ifndef NULL 
#define NULL ((void *)0)
#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE 1
#endif

#ifndef CHAR_T
typedef char CHAR_T;
#endif

//flash api test
#define UF_TEST_ADDR 0x3E3800   //由使用者指定flash操作地址，注意请选择uf分区中的地址
#define FLASH_TEST_BUFF "test"  //由使用者指定测试的数据
#define FLASH_TEST_CNT 100      //由使用者指定测试的次数

#define FLASH_UF_SIZE	0x8000	//uf分区大小，32K
#define FLASH_UF_ADDR	0x3E3000    //uf分区起始地址

//memory api test
#define MEMORY_OPERATE_CNT  1000    //由使用者指定操作次数

//thread api test
#define THREAD_OPERATE_CNT  5   //由使用者指定操作次数
typedef struct{
    THREAD_HANDLE handle;
    int exit;
}TEST_THREAD_S;

//mutex api test
typedef struct
{
	THREAD_HANDLE handle;
	MUTEX_HANDLE mutex;
	int exit;
	int *addr;
    char *buff;
}TEST_MUTEX_S;

//semaphore api test
typedef struct
{
	THREAD_HANDLE handle;
	SEM_HANDLE sem;
	int exit;
    int *num;
    int *flag;
}TEST_SEM_S;

//connect network test
#define UDP_RECV_MAX 1024
#define UDP_SERVER_PORT 7789
#define DEMO_DEF_AP_SSID_PF "SmartLife"
#define UDP_TIMEOUT_MAX 20  

//tcp transmission test
#define TCP_SERVER_PORT 7788
#define TCP_RECV_MAX    1024
#define TCP_SEND_MAX    1024
#define TCP_TIMEOUT_MAX 30

#define TEST_CONNECT_TIMEOUT    90

#define TEST_THREAD_PRIORITY    20  //测试程序中线程优先级

/////////////////////////////////////////////////////////////////////////////////////////////////
#define PR_ERR(fmt, ...)    printf("Test: [ERROR]"fmt"\r\n", ##__VA_ARGS__)
#define PR_WAR(fmt, ...)    printf("Test: [WARNING] "fmt"\r\n", ##__VA_ARGS__)
#define PR_DEBUG(fmt, ...)  printf("Test: [DEBUG] "fmt"\r\n", ##__VA_ARGS__)
/////////////////////////////////////////////////////////////////////////////////////////////////

//枚举
typedef enum _TUYA_TEST_TYPE_{
    E_TEST_ONE       = 0,
    E_TEST_TWO       = 1,
}TUYA_TEST_TYPE_E;

static void* thread1_func(void* arg)
{
    TEST_MUTEX_S *p_handle = (TEST_MUTEX_S*)arg;
    char buff[6] = "hello";
    int j = 0;
	
    tuya_hal_mutex_lock(p_handle->mutex);
    PR_DEBUG("mutex lock in thread1.\n");
    while(1)
    {
        p_handle->buff[(*(p_handle->addr))++] = buff[j++];
        if(j>4)
            {
                break;
            }
        //PR_WAR("%d .\n", *(p_handle->addr));
        tuya_hal_system_sleep(1000);
    }
	
    tuya_hal_mutex_unlock(p_handle->mutex);
    PR_DEBUG("mutex unlock in thread1.\n");
	
    tuya_hal_thread_release(p_handle->handle);
    PR_WAR("mutex test thread1_func exit.\n");
    p_handle->exit = 1;
}

static void* thread2_func(void* arg)
{
    TEST_MUTEX_S *p_handle = (TEST_MUTEX_S*)arg;
    char buf_2[6] = "world";
    int j = 0;
	
    tuya_hal_mutex_lock(p_handle->mutex);
    PR_DEBUG("mutex lock in thread2.\n");
    while(1)
    {
        p_handle->buff[(*(p_handle->addr))++] = buf_2[j++];
        if(j>4)
            {
                break;
            }
        //PR_WAR("%d .\n", *(p_handle->addr));
        tuya_hal_system_sleep(1000);
    }
    tuya_hal_mutex_unlock(p_handle->mutex);
    PR_DEBUG("mutex unlock in thread2.\n");
	
    tuya_hal_thread_release(p_handle->handle);
    PR_WAR("mutex test thread2_func exit.\n");  
    p_handle->exit = 1;
}

static void* thread3_func(void* arg)
{
    TEST_SEM_S *handle = (TEST_SEM_S*)arg;
    int i = 0;
    for(i=0; i<5; i++)  //循环5次
    {
        if(tuya_hal_semaphore_post(handle->sem) != OPRT_OK)
        {
            PR_ERR(" thread3_func tuya_hal_semaphore_post use err.\n");
            break;
        }
        PR_DEBUG("thread3_func post sem success.\n");
		
        (*(handle->num))++;
		PR_DEBUG("sem test thread3 : %d.\n", *(handle->num));
        tuya_hal_system_sleep(3000);
        if(*(handle->num) != 0)
        {
            PR_ERR(" thread3 test sem failed.\n");
            break;
        }
    }
	
    if(i == 5 && *(handle->num) == 0)
    {
		handle->exit = 1; 	//测试成功
        PR_DEBUG("sem thread3 work end, exit : %d, num : %d.\n", handle->exit, *(handle->num));
    }
	else
	{
		handle->exit = -1;
        *(handle->flag) = -1;
        PR_DEBUG("sem thread3 work end, exit : %d, num : %d, flag : %d.\n", handle->exit, *(handle->num), *(handle->flag));
	}
	
    tuya_hal_semaphore_release(handle->sem);
    tuya_hal_thread_release(handle->handle);
    PR_WAR("sem test thread3_func exit.\n");   
}

static void* thread4_func(void* arg)
{
    TEST_SEM_S *handle = (TEST_SEM_S*)arg;
    while((*(handle->flag) == 0) && (tuya_hal_semaphore_wait(handle->sem) == OPRT_OK))
    {
        PR_DEBUG("thread4_func wait sem success.\n");
        (*(handle->num))--;
		PR_DEBUG("sem test %d.\n", *(handle->num));
        if(*(handle->num) != 0)
        {
            //PR_ERR(" thread4 test sem failed.\n");
            break;
        }
    }
    tuya_hal_thread_release(handle->handle);
    PR_WAR("sem test thread4_func exit.\n");
    handle->exit = 1;
}

static void test_get_cb(const uint8_t *buf,const uint16_t len)
{
    PR_ERR(" please input the data of network to this func(), and then the SDK will parse them.\n");
}

static int client_func(void* arg)
{
    int fd = *(int*)arg;
    PR_DEBUG("welcome to client %d room.\n", fd);
    UNW_FD_SET_T readfds;
    char *recv_buff = tuya_hal_system_malloc(TCP_RECV_MAX);
    if(recv_buff == NULL){
        PR_ERR(" tcp transmission malloc recv_buff err.\n");
        return -1;
    }
    char *send_buff = tuya_hal_system_malloc(TCP_SEND_MAX);
    if(send_buff == NULL){
        PR_ERR(" tcp transmission malloc send_buff err.\n");
        tuya_hal_system_free(recv_buff);
        return -1;
    }
    int test_state = 0;
    int timeout_cnt = 0;
    int ret = 0;
    int exit_flag = 0;  //退出标志
    PR_WAR("please send \"begin test\" to the tcp server.\n");
    while(1)
    {
        if(timeout_cnt == TCP_TIMEOUT_MAX)
        {
            PR_ERR(" tcp : client %d timeout, close.\n");
            break;
        }
        UNW_FD_ZERO(&readfds);
        UNW_FD_SET(fd, &readfds);
        memset(recv_buff, 0, TCP_RECV_MAX);
        ret = tuya_hal_net_select(fd + 1, &readfds, NULL, NULL, 2*1000);
        if(ret <= 0 )
        {
            PR_ERR(" tcp : client socket %d select timeout.\n", fd);
            timeout_cnt++;
            continue;
        }
        if(UNW_FD_ISSET(fd, &readfds))
        {
            PR_ERR(" tcp : client socket %d has readfd.\n", fd);
            int recv_size = tuya_hal_net_recv(fd, recv_buff, TCP_RECV_MAX);
            if(recv_size <= 0)
            {
                PR_ERR(" tcp : Tcp socket recv fail.\n");
                break;
            }
            PR_DEBUG("tcp : client %d recv data : %s.\n", fd, recv_buff);
            PR_DEBUG("tcp : recv_size : %d.\n", recv_size);
            //数据解析环节
            switch(test_state)
                {
                    case 0:
                        {
                            if(strncmp(recv_buff, "begin test", 10) != 0){
                                PR_ERR(" tcp : client socket recv the test word : %s.\n", recv_buff);
                                ret = tuya_hal_net_send(fd, recv_buff, strlen(recv_buff));
                                if(ret <= 0)
                                {
                                    test_state = 0;
                                    PR_ERR(" tcp : client %d send tuya api test fail.\n", fd);
                                    exit_flag = -1;
                                    break;
                                }
                                break;
                            }
                            else
                                test_state = 1;
                        }
                    case 1:
                        {
                            //send "tuya api test"
                            int send_size = tuya_hal_net_send(fd, "Tuya api test", 14);
                            if(send_size <= 0)
                            {
                                test_state = 0;
                                PR_ERR(" tcp : client %d send tuya api test fail.\n", fd);
                                exit_flag = -1;
                                break;
                            }
                            PR_WAR("tcp : please send \"Tuya api test\" to the tcp server.\n");
                            test_state = 2;
                        }
                    case 2:
                        {
                            if(strncmp(recv_buff, "Tuya api test", 13) != 0){
                                ret = tuya_hal_net_send(fd, recv_buff, strlen(recv_buff));
                                if(ret <= 0)
                                {
                                    test_state = 0;
                                    PR_ERR(" tcp : client %d send tuya api test fail.\n", fd);
                                    exit_flag = -1;
                                    break;
                                }
                                PR_DEBUG("tcp : client %d recv tuya api test success.\n", fd);
                                break;
                            }
                            else
                                test_state = 3;
                        }
                    case 3:
                        {
                            PR_WAR("tcp : client %d tcp test over.\n");
                            exit_flag = 1;
                            break;
                        }
                    default:
                        {
                            PR_ERR(" tcp : recv data err, please send again.\n");
                            exit_flag = -1;
                            break;
                        }
                }
            if(exit_flag != 0)
                break;
        }
    }
    PR_DEBUG("exit flag : %d.\n", exit_flag);
    if(recv_buff){
        tuya_hal_system_free(recv_buff);
        recv_buff = NULL;
    }
    if(send_buff){
        tuya_hal_system_free(send_buff);
        send_buff = NULL;
    }
    return exit_flag;
}   




static int tuya_flash_api_test(void)
{
    printf("****************************************************\n");
    PR_WAR("1、enter the flash api test.\n");
    printf("****************************************************\n");
    //flash api test
    //example: bk7252 rtt uf_start_addr:3E3000, uf_size: 0x8000
    UNI_STORAGE_DESC_S *storge = tuya_hal_storage_get_desc();
    if(storge == NULL)
    {
        PR_ERR(" tuya_hal_storage_get_desc() use err, exit...\n");
        return -1;
    }
    UF_PARTITION_TABLE_S *uf = tuya_hal_uf_get_desc();
    if(NULL == uf) 
    {
        PR_ERR(" tuya_hal_uf_get_desc() use err, exit...\n");
        return -1;
    }

    //选取UF分区中的一块内存进行读写试验, 判断长度是否在UF分区内
    if((UF_TEST_ADDR + strlen(FLASH_TEST_BUFF) + FLASH_TEST_CNT) > (FLASH_UF_ADDR+FLASH_UF_SIZE)  \
        || UF_TEST_ADDR < FLASH_UF_ADDR)
    {
        PR_ERR(" flash addr 0x%x is useless, exit...\n", UF_TEST_ADDR);
        goto exit;
    }
    //加密数据
    int buff_len = sizeof(FLASH_TEST_BUFF);
        
#ifdef TEST_ENCRYPT
    char *encryed_buff = tuya_hal_system_malloc(buff_len);
    if(encryed_buff == NULL){
        PR_ERR(" encryed_buff malloc fail, exit...\n");
        goto exit;
    }
    char *dencryed_buff = tuya_hal_system_malloc(buff_len);
    if(dencryed_buff == NULL){
        PR_ERR(" dencryed_buff malloc fail, exit...\n");
        goto exit;
    }
#endif

    char *read_buff = tuya_hal_system_malloc(buff_len);
    if(read_buff == NULL){
        PR_ERR(" read_buff malloc fail, exit...\n");
        goto exit;
    }
    char *write_buff = tuya_hal_system_malloc(buff_len);
    if(write_buff == NULL){
        PR_ERR(" encryed_buff malloc fail, exit...\n");
        goto exit;
    }
#ifndef TEST_ENCRYPT
    memcpy(write_buff, FLASH_TEST_BUFF, buff_len);
#endif
    
    //计算开始时间
    unsigned int flash_tcnt1 = 0;
    unsigned int flash_tcnt2 = 0;
    
    int flash_cnt = 0;
    int flash_ret = 0;
    
    while(flash_cnt < FLASH_TEST_CNT)
    {
#ifdef TEST_ENCRYPT
        memset(encryed_buff, 0, buff_len);
        memset(dencryed_buff, 0, buff_len);
        memset(write_buff, 0, buff_len);
#endif
        memset(read_buff, 0, buff_len);

        //加密
#ifdef TEST_ENCRYPT
        if(encrypt_api(write_buff, FLASH_TEST_BUFF) != OPRT_OK){
            PR_ERR(" encrypt_api use err.\n");
            goto exit;
        }
#endif

        flash_tcnt1 = tuya_hal_get_systemtickcount();
        //擦除数据
        flash_ret = tuya_hal_flash_erase(UF_TEST_ADDR+flash_cnt, buff_len-1);
        if(flash_ret != OPRT_OK)
        {
            PR_ERR(" tuya_hal_flash_erase addr:0x%x, size:%d.\n", UF_TEST_ADDR+flash_cnt, buff_len-1);
            break;
        }
        //写入数据
        flash_ret = tuya_hal_flash_write(UF_TEST_ADDR+flash_cnt, write_buff, buff_len-1);
        if(flash_ret != OPRT_OK)
        {
            PR_ERR(" tuya_hal_flash_write addr:0x%x, size:%d.\n", UF_TEST_ADDR+flash_cnt, buff_len-1);
            break;
        }
        //读取数据
        flash_ret = tuya_hal_flash_read(UF_TEST_ADDR+flash_cnt, read_buff, buff_len-1);
        if(flash_ret != OPRT_OK)
        {
            PR_ERR(" tuya_hal_flash_read addr:0x%x, size:%d.\n", UF_TEST_ADDR+flash_cnt, buff_len-1);
            break;
        }
        flash_tcnt2 = tuya_hal_get_systemtickcount() - flash_tcnt1 + flash_tcnt2;

#ifdef TEST_ENCRYPT
        //解密数据
        if(dencryed_api(dencryed_buff, read_buff) != OPRT_OK){
            PR_ERR(" dencryed_api use err.\n");
            goto exit;
        }
        if(strcmp(dencryed_buff, FLASH_TEST_BUFF) != 0)
        {
            PR_ERR(" flash test read buff err, exit...\n");
            goto exit;
        }
#else
        //比较数据
        //PR_DEBUG("read_buff : %s.\n", read_buff);
        if(strcmp(read_buff, FLASH_TEST_BUFF) != 0)
        {
            PR_ERR(" flash test read buff err, exit...\n");
            goto exit;
        }
#endif

        flash_cnt ++;
    }
    if(flash_cnt != FLASH_TEST_CNT)
        goto exit;
    
    //计算时间
    unsigned int flash_tms = flash_tcnt2 * tuya_hal_get_tickratems();
    PR_WAR("flash api earse/write/read %d times cost %dms.\n", FLASH_TEST_CNT, flash_tms);
    PR_WAR("average time = %f.\n", flash_tms/(1.0*FLASH_TEST_CNT));
    return 0;
    
exit:
#ifdef TEST_ENCRYPT
    if(encryed_buff)
        tuya_hal_system_free(encryed_buff);
    if(dencryed_buff)
        tuya_hal_system_free(dencryed_buff);
#endif
    if(read_buff)
        tuya_hal_system_free(read_buff);
    if(write_buff)
        tuya_hal_system_free(write_buff);
    
    PR_ERR(" flash api test err, exit...\n");
    return -1;
}

static int tuya_memory_api_test(void)
{
    //memory test
    printf("****************************************************\n");
    PR_WAR("2、enter the memory api test...\n");
    printf("****************************************************\n");
    
    static int size_array[] = {20, 32, 65, 128, 512, 1024, 4096, 10240, 16384};
    int malloc_err_cnt = 0;
    int i = 0;
    int *ptr = NULL;
    for(i=0; i<sizeof(size_array)/sizeof(size_array[0]); i++)
    {
        PR_DEBUG("size_array[%d] = %d.\n", i, size_array[i]);
        int j = MEMORY_OPERATE_CNT;
        //开始时间
        unsigned int tcnt1 = tuya_hal_get_systemtickcount();
        PR_DEBUG("begin time %d.\n", tcnt1);
        while(j-- > 0)
        {
            //申请空间
            ptr = tuya_hal_system_malloc(size_array[i]);
            if(ptr == NULL)
            {
               malloc_err_cnt++;
            }
            //释放空间
            tuya_hal_system_free(ptr);
            ptr = NULL;
        }
		
        //结束时间
        unsigned int tcnt2 = tuya_hal_get_systemtickcount();
        PR_DEBUG("end time %d.\n", tcnt2);
        //计算平均时间，并提示
        unsigned int tms = (tcnt2 - tcnt1) * tuya_hal_get_tickratems();
        PR_WAR("operate malloc and free size = %d, cost %dms, average operating time is %fms, malloc fail cnt is %d.\n",   \
                    size_array[i], tms, tms/(MEMORY_OPERATE_CNT*1.0), malloc_err_cnt);
   }
   return 0;
}

static void *thread_api_func(void* arg)
{
    TEST_THREAD_S *p_handle = (TEST_THREAD_S *)arg;
    PR_DEBUG("p_handle->exit = %d.\n", p_handle->exit);
    PR_DEBUG("thread_api_func enter.\n");
    int i = 0;
    for(i=0; i<5; i++)
        PR_DEBUG("thread working...\n");
    tuya_hal_thread_release(p_handle->handle);
    p_handle->exit = 2; //线程工作完成状态
    PR_DEBUG("p_handle->exit = %d.\n", p_handle->exit);
}

static int tuya_thread_api_test(void)
{
    //thread api test
    PR_WAR("3、enter the thread api test...\n");

    int thread_num = 0;
    TEST_THREAD_S *thread_handle = tuya_hal_system_malloc(sizeof(TEST_THREAD_S));
    if(thread_handle == NULL){
        PR_ERR(" thread test thread handle malloc fail.\n");
        return -1;
    }
    thread_handle->exit = 0;    //  初始状态
    
    while(thread_num < THREAD_OPERATE_CNT)
    {
        if(thread_handle->exit != 1){
            memset(thread_handle, 0, sizeof(TEST_THREAD_S));
            thread_handle->exit = 1;    //线程创建中
            if(tuya_hal_thread_create(&thread_handle->handle, "test", 1024, TEST_THREAD_PRIORITY, thread_api_func, (void *)thread_handle) != OPRT_OK){
                thread_handle->exit = 3;    //创建失败状态
                break;
            }
            else
                thread_num++;
       }
        else
            tuya_hal_system_sleep(1000);
    }
    while(thread_handle->exit != 2 && thread_handle->exit != 3)
        tuya_hal_system_sleep(1000);
    tuya_hal_system_free(thread_handle);
    if(thread_num != THREAD_OPERATE_CNT)
    {
        PR_ERR("  thread api test err, operate cnt = %d...\n", thread_num);
        return -1;
    }
    return 0;
}

static int tuya_mutex_api_test()
{
    //mutex test
	printf("****************************************************\n");
    PR_WAR("4、enter the mutex api test...\n");
	printf("****************************************************\n");

    MUTEX_HANDLE mutex = NULL;
    if(tuya_hal_mutex_create_init(&mutex) != OPRT_OK)
    {
        PR_ERR(" tuya_hal_mutex_create_init use err.\n");
        return -1;
    }
    if(mutex == NULL){
        PR_ERR(" mutex create fail, mutex is NULL.\n");
        return -1;
    }
    
    TEST_MUTEX_S *mutex_handle1 = tuya_hal_system_malloc(sizeof(TEST_MUTEX_S));
    if(mutex_handle1 == NULL){
        PR_ERR(" mutex api test, mutex_handle1 malloc err.\n");
        return -1;
    }
    
    TEST_MUTEX_S *mutex_handle2 = tuya_hal_system_malloc(sizeof(TEST_MUTEX_S));
    if(mutex_handle2 == NULL){
        PR_ERR(" mutex api test, mutex_handle2 malloc err.\n");
        tuya_hal_system_free(mutex_handle1);
        return -1;
    }

    int addr = 0;
    char test_buf[11] = {0};
    
    memset(mutex_handle1, 0, sizeof(TEST_MUTEX_S));
    memset(mutex_handle2, 0, sizeof(TEST_MUTEX_S));
    
    mutex_handle1->mutex = mutex;
    mutex_handle2->mutex = mutex;
    mutex_handle1->addr = &addr;
    mutex_handle2->addr = &addr;
    mutex_handle1->buff = &test_buf;
    mutex_handle2->buff = &test_buf;
    
    int n_ret = tuya_hal_thread_create(&mutex_handle1->handle, "mutex_thread1", 1024, TEST_THREAD_PRIORITY, thread1_func, (void *)mutex_handle1);
    if(n_ret != OPRT_OK)
    {
        PR_ERR(" Create thread1 error:%d \n", n_ret);
		return -1;
    }
    n_ret = tuya_hal_thread_create(&mutex_handle2->handle, "mutex_thread2", 1024, TEST_THREAD_PRIORITY, thread2_func, (void *)mutex_handle2);
    if(n_ret != OPRT_OK)
    {
        PR_ERR("Create thread2 error:%d \n", n_ret);
		return -1;
    }
    PR_DEBUG("mutex thread create ok.\n");
    int timeout_cnt = 15;
    while((timeout_cnt-- > 0) && (mutex_handle1->exit == 0 || mutex_handle2->exit == 0))
        tuya_hal_system_sleep(1000);
    
    test_buf[10] = '\0';
    printf("Test: [DEBUG]mutex test, buf : %s===\n", test_buf);

    //检测结果
    tuya_hal_system_free(mutex_handle1);
    tuya_hal_system_free(mutex_handle2);
    tuya_hal_mutex_release(mutex);
    if(strcmp(test_buf, "helloworld") != 0)
    {
        PR_ERR(" mutes test err, exit.\n");
        return -1;
    }
    return 0;
}

static int tuya_semaphore_api_test()
{
	printf("****************************************************\n");
    PR_WAR("5、enter the semaphore api test...\n");
	printf("****************************************************\n");

	int ret = 0;
	TEST_SEM_S *sem_handle1 = tuya_hal_system_malloc(sizeof(TEST_SEM_S));
	if(sem_handle1 == NULL)
	{
		PR_ERR(" tuya_hal_system_malloc sem_handle1 err.\n");
		return -1;
	}
	TEST_SEM_S *sem_handle2 = tuya_hal_system_malloc(sizeof(TEST_SEM_S));
	if(sem_handle2 == NULL)
	{
		PR_ERR(" tuya_hal_system_malloc sem_handle2 err.\n");
		tuya_hal_system_free(sem_handle1);
		return -1;
	}	
	
    SEM_HANDLE semaphore = NULL;
    if(tuya_hal_semaphore_create_init(&semaphore, 0, 1) != OPRT_OK)
    {
        PR_ERR(" tuya_hal_semaphore_create_init use err.\n");
        return -1;
    }
    if(semaphore == NULL){
        PR_ERR(" semaphore create fail, semaphore is NULL.\n");
        return -1;
    }
    printf("semaphore addr : 0x%x.\n", semaphore);

    int num = 0;
    int flag = 0;
	sem_handle1->sem = semaphore;
	sem_handle2->sem = semaphore;
	sem_handle1->exit = 0;
	sem_handle2->exit = 0;
    sem_handle1->num = &num;
	sem_handle2->num = &num;
	sem_handle1->flag = &flag;
	sem_handle2->flag = &flag;

    int n_ret = tuya_hal_thread_create(&sem_handle1->handle, "mutex_thread3", 1024, TEST_THREAD_PRIORITY, thread3_func, (void *)sem_handle1);
    if(n_ret != OPRT_OK)
    {
        PR_ERR(" Create thread1 error:%d \n", n_ret);
		return -1;
    }
    n_ret = tuya_hal_thread_create(&sem_handle2->handle, "mutex_thread4", 1024, TEST_THREAD_PRIORITY, thread4_func, (void *)sem_handle2);
    if(n_ret != OPRT_OK)
    {
        PR_ERR(" Create thread2 error:%d \n", n_ret);
		return -1;
    }
    while(sem_handle1->exit == 0 || sem_handle2->exit == 0)
        tuya_hal_system_sleep(1000);
    if(sem_handle1->exit == -1)
    {
        PR_ERR(" semaphore test err.\n");
        ret = -1;
    }
	tuya_hal_system_free(sem_handle1);
	tuya_hal_system_free(sem_handle2);
    return ret;
}

static int tuya_smart_mode_test(char *ssid, char *passwd)
{
    //smart mode test
    //断开连接
    int ret = 0;
    ret = tuya_hal_wifi_station_disconnect();
    if(ret != OPRT_OK)
    {
        PR_ERR(" tuya_hal_wifi_station_disconnect() use err.\n");
        return -1;
    }
    tuya_hal_system_sleep(5000);

    //设置work_mode为STATION
    ret = tuya_hal_wifi_set_work_mode(WWM_STATION);
    if(ret != OPRT_OK)
    {
        PR_ERR(" tuya_hal_wifi_set_work_mode set station mode fail.\n");
        return -1;
    }
    
#if 1
    //扫描当前环境中存在的ap
    AP_IF_S *ap_ary = NULL;
    int ap_num = 0;
    ret = tuya_hal_wifi_all_ap_scan(&ap_ary,&ap_num);
    if(ret != OPRT_OK || ap_num == 0)
    {
        PR_ERR(" tuya_hal_wifi_all_ap_scan use err.\n");
        return -1;
    }
    else
    {
        int i;
        for(i=0; i<ap_num; i++)
        {
            printf("channel:%02d bssid:%02x-%02x-%02x-%02x-%02x-%02x rssi:%3d ssid:%s", ap_ary[i].channel, \
                    ap_ary[i].bssid[0], ap_ary[i].bssid[1], ap_ary[i].bssid[2],\
                    ap_ary[i].bssid[3], ap_ary[i].bssid[4], ap_ary[i].bssid[5],\
                    ap_ary[i].rssi, ap_ary[i].ssid);
        }
    }
	ret = tuya_hal_wifi_release_ap(ap_ary);
	if(ret != OPRT_OK)
    {
        PR_ERR(" tuya_hal_wifi_release_ap use err.\n");
        return -1;
    }
#endif

    //获取station模式下的mac地址
    NW_MAC_S mac;
    memset(&mac, 0, sizeof(NW_MAC_S));
    ret = tuya_hal_wifi_get_mac(WF_STATION, &mac);
    if(ret != OPRT_OK)
    {
        PR_ERR(" tuya_hal_wifi_get_mac get station mac fail.\n");
        //释放扫描到的ap资源
        //todo
        return -1;
    }

    //设置work_mode为sniffer模式
    ret = tuya_hal_wifi_set_work_mode(WWM_SNIFFER);
    if(ret != OPRT_OK)
    {
        PR_ERR(" tuya_hal_wifi_set_work_mode set sniffer mode fail.\n");
        return -1;
    }

    //将解析函数传递给设备
    ret = tuya_hal_wifi_sniffer_set(true, test_get_cb);
    if(ret != OPRT_OK)
    {
        PR_ERR(" tuya_hal_wifi_sniffer_set use err.\n");
        return -1;
    }

    //这里的解析不好实现，所以使用Ap mode的ssid和password来实现这一模拟流程
    char chan = 0;
    ret = tuya_hal_wifi_get_cur_channel(&chan);
    if(ret != OPRT_OK)
    {
        PR_ERR(" tuya_hal_wifi_get_cur_channel use err.\n");
        return -1;
    }
    else
    {
        PR_DEBUG("tuya_hal_wifi_get_cur_channel chan = %d.\n", chan);
    }

    //设置work_mode为station模式
    ret = tuya_hal_wifi_set_work_mode(WWM_STATION);
    if(ret != OPRT_OK)
    {
        PR_ERR(" tuya_hal_wifi_set_work_mode set station mode fail.\n");
        return -1;
    }

    //连网
    PR_DEBUG("Smart mode ssid : %s, passwd : %s.\n", ssid, passwd);
    ret = tuya_hal_wifi_station_connect(ssid, passwd);
    if(ret != OPRT_OK)
    {
         PR_ERR(" tuya_hal_wifi_station_connect use err.\n");
         return -1;
    }

    int mode = 0;
    //获得当前的work_mode
    ret = tuya_hal_wifi_get_work_mode(&mode);
    if(ret != OPRT_OK || mode != WWM_STATION)
    {
        PR_ERR(" current work_mode is not station.\n");
        return -1;
    }
    
     //等待连接网络成功
    int test_state = 0;
    int wifi_status = 0;
    int cnt = TEST_CONNECT_TIMEOUT;
    while(cnt-- > 0)
    {
        if(test_state == 1)
            break;
        if(tuya_hal_wifi_station_get_status(&wifi_status) == OPRT_OK)
        {
            switch(wifi_status)
            {
                case WSS_CONNECTING:
                    PR_WAR("connecting wifi...\n");
                    break;
                case WSS_PASSWD_WRONG:
                    PR_ERR(" wifi password is wrong, exit...\n");
                    break;
                case WSS_NO_AP_FOUND:
                    PR_ERR(" ap not find, exit...");
                    break;
                case WSS_CONN_FAIL:
                    PR_ERR(" connect wifi fail, exit...\n");
                    break;
                case WSS_CONN_SUCCESS:
                    PR_WAR("wifi connected...\n");
                    break;
                case WSS_GOT_IP:
                    PR_WAR("got ip success...\n");
                    test_state = 1;
                    break;
            }
            tuya_hal_system_sleep(1000);
        }
    }

    printf("****************************************************\n");
    if(test_state != 1)
    {
        PR_ERR(" Smart mode test fail, exit...\n");
        ret = -1;
    }
    else
        PR_WAR("Smart mode test success.\n");
    printf("****************************************************\n");
    return ret;
}

static int tuya_network_test()
{
    //配网流程模拟测试        
    printf("****************************************************\n");
    PR_WAR("6、enter connect network test\n");
    printf("****************************************************\n");
    char *serial_no = NULL;
    int ret = 0;

    //新基线SDK没有这个api
#if 0
    if((serial_no = tuya_hal_get_serialno()) == NULL)
    {
        PR_ERR(" tuya_hal_get_serialno() use error.\n");
        return -1;
    }
    PR_DEBUG("get serial number : %s.\n", serial_no);
#endif
        
    //ret = tuya_hal_wifi_set_country_code(COUNTRY_CODE_CN);
    ret = tuya_hal_wifi_set_country_code("CN");
    if(ret != OPRT_OK)
    {
        PR_ERR(" tuya_hal_wifi_set_country_code() use error.\n");
        return -1;
    }
        
    PR_DEBUG("operate the flash ing...\n");
    tuya_hal_system_sleep(2000);
    PR_DEBUG("operate the falsh end.\n");
            
    PR_DEBUG("enter the Ap mode...\n");
    ret = tuya_hal_wifi_set_work_mode(WWM_SOFTAP);
    if(ret != OPRT_OK)
    {
        PR_ERR(" tuya_hal_wifi_set_work_mode set softap mode error.\n");
        return -1;
    }
#if 0
    nt work_mode = 0;
    ret = tuya_hal_wifi_get_work_mode(&work_mode);
    if(work_mode != WWM_SOFTAP)
    {
        PR_ERR(" tuya_hal_wifi_get_work_mode work_mode != WWM_SOFTAP.\n");
        return -1;
    }
#endif
    
    NW_MAC_S mac;
    memset(&mac, 0, sizeof(NW_MAC_S));
    ret = tuya_hal_wifi_get_mac(WF_STATION, &mac);
    if(ret != OPRT_OK)
    {
        PR_ERR(" tuya_hal_wifi_get_mac() use error");
        return -1;
    }
            
    WF_AP_CFG_IF_S ApCfg;
    memset(&ApCfg, 0, sizeof(WF_AP_CFG_IF_S));
    memcpy(ApCfg.ssid,DEMO_DEF_AP_SSID_PF,strlen(DEMO_DEF_AP_SSID_PF));
    sprintf((CHAR_T *)ApCfg.ssid,"%s-%02X%02X",(CHAR_T *)ApCfg.ssid,mac.mac[4],mac.mac[5]);
    ApCfg.s_len = strlen(DEMO_DEF_AP_SSID_PF);
    ApCfg.md = WAAM_OPEN;
    ApCfg.s_len += 5;
    PR_DEBUG("the name of AP is %s.\n", ApCfg.ssid);
	
    //起Ap热点
    ret = tuya_hal_wifi_ap_start(&ApCfg);
    if(ret != OPRT_OK)
    {
        PR_ERR(" tuya_hal_wifi_ap_start use error.\n");
        return -1;
    }
	
    tuya_hal_system_sleep(1000);
    //创建udp-server，接收配网配置信息：ssid and password
    int test_udp_fd = tuya_hal_net_socket_create(PROTOCOL_UDP);
    if(test_udp_fd < 0)
    {
        PR_ERR(" Udp socket create fail, test_udp_fd : %d, error:%d.\n", test_udp_fd, tuya_hal_net_get_errno());
        return -1;
    }
	
    PR_DEBUG("test_udp_fd = %d.\n", test_udp_fd);
    int test_udp_status = tuya_hal_net_set_reuse(test_udp_fd);
    if(test_udp_status < 0)
    {
        PR_ERR(" Udp socket set reuse fail.\n");
        tuya_hal_net_close(test_udp_fd);
        return -1;
    }
	
    tuya_hal_net_set_block(test_udp_fd, FALSE);
    test_udp_status = tuya_hal_net_bind(test_udp_fd,TY_IPADDR_ANY,UDP_SERVER_PORT);
    if(test_udp_status < 0)
    {
        PR_ERR(" Udp socket bind fail.\n");
        tuya_hal_net_close(test_udp_fd);
        return -1;
    }
    PR_WAR("please send ssid and password, like \"ssid:xxxx,pw:xxxx\"\n");

    UNW_FD_SET_T readfds;
    char test_recv_buff[UDP_RECV_MAX] = {0};
    UNW_IP_ADDR_T test_client_ip_addr = 0;
    int test_client_port = 0;
    int test_state = 0;
    int timeout_cnt = 0;
    char wifi_ssid[32] = {0};
    char wifi_password[64] = {0};

    while(timeout_cnt < UDP_TIMEOUT_MAX)
    {
        UNW_FD_ZERO(&readfds);
        UNW_FD_SET(test_udp_fd,&readfds);
        memset(test_recv_buff, 0, UDP_RECV_MAX);
        timeout_cnt++;
        ret = tuya_hal_net_select(test_udp_fd + 1,&readfds,NULL,NULL,5*1000);
        if(ret <= 0 )
        {
            PR_ERR(" Udp socket select timeout.\n");
            continue;
        }
		
        if(UNW_FD_ISSET(test_udp_fd,&readfds))
        {
            PR_DEBUG("Udp socket has readfd.\n");
            int recv_size = tuya_hal_net_recvfrom(test_udp_fd, test_recv_buff, sizeof(test_recv_buff), &test_client_ip_addr, &test_client_port);
            if(recv_size <= 0)
            {
                PR_ERR(" Udp test: recv nothing.\n");
                test_state = -1;
                break;
            }
            PR_DEBUG("Udp Server recv %s from client ip %d, port %d.\n", test_recv_buff, test_client_ip_addr, test_client_port);
			
            timeout_cnt = 0;
            //切割字符串获得ssid和password
            if(strlen(test_recv_buff) <= 9)
            {
                PR_WAR("please send ssid and password, format: \"ssid:xxxx,pw:xxxx\"");
                continue;
            }
			
            if(strstr(test_recv_buff, "ssid:") == NULL || strstr(test_recv_buff, ";pw:") == NULL)
            {
                PR_WAR("please send ssid and password, format: \"ssid:xxxx,pw:xxxx\"");
                continue;
            }
			
            if(strstr(test_recv_buff, "ssid:") != &test_recv_buff[0])
            {
                PR_WAR("please send ssid and password, format: \"ssid:xxxx,pw:xxxx\"");
                continue;
            }
			
            test_state = 1;
            break;
        }
    }

    tuya_hal_net_close(test_udp_fd);
    //关闭Ap热点
    ret = tuya_hal_wifi_ap_stop();
    if(ret != OPRT_OK)
    {
        PR_ERR(" tuya_hal_wifi_ap_stop use error.\n");
        return -1;
    }
	
    if(test_state == 1)//获得ssid和password
    {
        //解析ssid和passwd
        PR_DEBUG("Ap mode wifi config : %s.=\n", test_recv_buff);
        char *passwd = strstr(test_recv_buff, ";pw:");
        memcpy(wifi_ssid, test_recv_buff+5, passwd-test_recv_buff-5);
        wifi_ssid[passwd-test_recv_buff-5] = '\0';
        PR_DEBUG("Ap mode get ssid : %s.=\n", wifi_ssid);
        passwd = passwd + 4;
        int i = 0;
        while(*passwd != '\r' && *passwd != '\n'){
            memcpy(&wifi_password[i], passwd, 1);
            i++;
            passwd++;
        }
		
        wifi_password[i] = '\0';
        PR_DEBUG("Ap mode get passwd : %s.=\n", wifi_password);
        PR_DEBUG("get ssid and password success.\n");

       //设置work_mode为STATION模式
       ret = tuya_hal_wifi_set_work_mode(WWM_STATION);
       if(ret != OPRT_OK)
       {
            PR_ERR(" tuya_hal_wifi_set_work_mode set station mode fail.\n");
            return -1;
       }
       
       //将ssid和password传递给设备，连接网络
       PR_DEBUG("wifi_ssid : %s, wifi_password : %s.\n", wifi_ssid, wifi_password);
       ret = tuya_hal_wifi_station_connect(wifi_ssid,wifi_password);
       
       //获取当前的work_mode
       WF_WK_MD_E mode = 0;
       ret = tuya_hal_wifi_get_work_mode(&mode);
       if(ret != OPRT_OK || mode != WWM_STATION)
       {
           PR_ERR(" tuya_hal_wifi_get_work_mode use err or work mode is not station.\n");
           //断开网络连接
           //todo
           tuya_hal_wifi_station_disconnect();
           return -1;
       }
    }
    else
    {
        PR_ERR(" network test get wifi config err.\n");
        PR_DEBUG("test fail, exit.\n");
        return -1;
    }

    //等待连接网络成功
    test_state = 0;
    WF_STATION_STAT_E wifi_status = 0;
    int cnt = TEST_CONNECT_TIMEOUT;
    //todo:需要增加对连接错误状态的判断进行退出test
    while(cnt-- > 0)
    {
        if(test_state == 1)
            break;
		
        if(tuya_hal_wifi_station_get_status(&wifi_status) == OPRT_OK)
        {
            switch(wifi_status)
            {
                case WSS_CONNECTING:
                    PR_WAR("connecting wifi...\n");
                    break;
                case WSS_PASSWD_WRONG:
                    PR_ERR(" wifi password is wrong, exit...\n");
                    break;
                case WSS_NO_AP_FOUND:
                    PR_ERR(" ap not find, exit...");
                    break;
                case WSS_CONN_FAIL:
                    PR_ERR(" connect wifi fail, exit...\n");
                    break;
                case WSS_CONN_SUCCESS:
                    PR_WAR("wifi connected...\n");
                    break;
                case WSS_GOT_IP:
                    PR_WAR("got ip success...\n");
                    test_state = 1;
                    break;
            }
        }
        tuya_hal_system_sleep(1000);
    }
    
    printf("****************************************************\n");
    if(test_state != 1)
    {
        PR_ERR(" Ap mode test fail, exit...\n");
        tuya_hal_wifi_station_disconnect();
        ret = -1;;
    }
    else
    {
        PR_WAR("Ap mode test success.\n");
    }
    printf("****************************************************\n");

#if 1
    PR_WAR("Smart mode test begin...\n");
    if(tuya_smart_mode_test(wifi_ssid, wifi_password) != OPRT_OK)
        return -1;
#endif
    return ret;

}

static int tuya_tcp_transmission_test(void)
{
    int tcp_fd = 0;
    int tcp_status = 0;
    
    tcp_fd = tuya_hal_net_socket_create(PROTOCOL_TCP);
    if(tcp_fd < 0)
    {
        PR_ERR(" tcp : Tcp socket create fail, tcp_fd : %d, error:%d.\n", tcp_fd, tuya_hal_net_get_errno());
        return -1;
    }
    PR_DEBUG("tcp :tcp_fd = %d.\n", tcp_fd);
    tcp_status = tuya_hal_net_set_reuse(tcp_fd);
    if(tcp_status < 0)
    {
        PR_ERR(" tcp :Tcp socket set reuse fail.\n");
        tuya_hal_net_close(tcp_fd);
        return -2;
    }
    
    tcp_status = tuya_hal_net_bind(tcp_fd,TY_IPADDR_ANY,TCP_SERVER_PORT);
    if(tcp_status < 0)
    {
        PR_ERR(" tcp :Tcp socket bind fail.\n");
        tuya_hal_net_close(tcp_fd);
        return -3;
    }
    tcp_status = tuya_hal_net_listen(tcp_fd, 5);
    if(tcp_status < 0)
    {
        PR_ERR(" tcp :Tcp socket listen fail.\n");
        tuya_hal_net_close(tcp_fd);
        return -4;
    }
    
    UNW_FD_SET_T tcp_readfds;
    int client_fd = -1; 
    int ret = 0;
    while(1)
    {
        PR_DEBUG("tcp :Tcp socket begin select.\n");
        UNW_FD_ZERO(&tcp_readfds);
        UNW_FD_SET(tcp_fd,&tcp_readfds);
        ret = tuya_hal_net_select(tcp_fd + 1,&tcp_readfds,NULL,NULL,10*1000);
        if(ret <= 0 )
        {
            PR_ERR(" tcp :Tcp socket select timeout.\n");
            continue;
        }
        if(UNW_FD_ISSET(tcp_fd,&tcp_readfds))
        {
            PR_ERR(" tcp :Tcp socket has readfd.\n");
            UNW_IP_ADDR_T addr = 0;
            client_fd = tuya_hal_net_accept(tcp_fd,&addr,NULL);
            if(client_fd < 0)
            {
                PR_ERR(" tcp :Tcp socket accept fail.\n");
                break;
            }
            PR_DEBUG("tcp :Tcp client connected, client_fd %d.\n", client_fd);
            break;
        }
    
    }
    if(client_fd < 0)
    {
        PR_ERR(" tcp : tcp transmission test err.\n");
        return -1;
    }
    tuya_hal_net_set_reuse(client_fd);
    tuya_hal_net_set_block(client_fd, FALSE);
    ret = client_func(&client_fd);
    if(ret == 1)
    {
        ret = 0;
        PR_DEBUG("tcp test over.\n");
    }
    else
    {
        PR_ERR(" tcp :Tcp scoket clean the session %d resource", client_fd);
        ret = -1;
    }

    //tuya_hal_net_shutdown(client_fd, 2);
    tuya_hal_net_close(tcp_fd);
    return ret;
}

static int tuya_udp_transmission_test()
{
    printf("****************************************************\n");
    PR_WAR("udp : udp transmission test begin.\n");
    printf("****************************************************\n");
    int ret = 0;
    //udp test
    int udp_fd = 0;
    int udp_status = 0;
    
    udp_fd = tuya_hal_net_socket_create(PROTOCOL_UDP);
    if(udp_fd < 0)
    {
        PR_ERR(" Udp socket create fail, tcp_fd : %d, error:%d.\n", udp_fd, tuya_hal_net_get_errno());
        return -1;
    }
    PR_DEBUG("Udp socket udp_fd = %d.\n", udp_fd);
    udp_status = tuya_hal_net_set_reuse(udp_fd);
    if(udp_status < 0)
    {
        PR_ERR(" Udp socket set reuse fail.\n");
        tuya_hal_net_close(udp_fd);
        return -1;
    }
    tuya_hal_net_set_block(udp_fd, FALSE);
    
    udp_status = tuya_hal_net_bind(udp_fd,TY_IPADDR_ANY,UDP_SERVER_PORT);
    if(udp_status < 0)
    {
        PR_ERR(" Udp socket bind fail.\n");
        tuya_hal_net_close(udp_fd);
        return -1;
    }
    
    UNW_FD_SET_T udp_readfds;
    
    int i = 0;
    char *recv_buff = tuya_hal_system_malloc(UDP_RECV_MAX);
    if(recv_buff == NULL){
        PR_ERR(" Udp socket recv_buff malloc err.\n");
        tuya_hal_net_close(udp_fd);
        return -1;
    }
    UNW_IP_ADDR_T client_ip_addr = 0;
    int client_port = 0;
    UNW_IP_ADDR_T last_client_ip_addr = 0;
    int last_client_port = 0;
    int udp_state = 0;  //初始状态
    int timeout_cnt = 0;    //超时次数
    while(timeout_cnt < UDP_TIMEOUT_MAX)
    {
        int ret = 0;
        PR_DEBUG("Udp socket begin select.\n");
        UNW_FD_ZERO(&udp_readfds);
        UNW_FD_SET(udp_fd,&udp_readfds);
        memset(recv_buff, 0, UDP_RECV_MAX);
        ret = tuya_hal_net_select(udp_fd + 1,&udp_readfds,NULL,NULL,3*1000);
        if(ret <= 0 )
        {
            PR_ERR(" Udp socket select timeout.\n");
            continue;
        }
        timeout_cnt++;
        if(UNW_FD_ISSET(udp_fd,&udp_readfds))
        {
            PR_DEBUG("Udp socket has readfd.\n");
            UNW_IP_ADDR_T addr = 0;
            int recv_size = tuya_hal_net_recvfrom(udp_fd, recv_buff, UDP_RECV_MAX, &client_ip_addr, &client_port);
            if(recv_size <= 0)
            {
                PR_ERR(" Udp test: recv nothing.\n");
                break;
            }
            PR_DEBUG("Udp Server recv %s from client ip %d, port %d.\n", recv_buff, client_ip_addr, client_port);
            timeout_cnt = 0;
            //收到的客户端和上一个收到的客户端不同，则重新开始验证过程
            if(udp_state != 2 && (last_client_ip_addr != client_ip_addr || last_client_port != client_port))
            {
                udp_state = 0;
                PR_WAR("Udp test: please send \"begin test\" to the udp server.\n");
                last_client_ip_addr = client_ip_addr;
                last_client_port = client_port;
                continue;
            }
        
            if(udp_state == 0)
            {
                if(strncmp(recv_buff, "begin test", 10) != 0)
                {
                    udp_state = 0;
                    PR_WAR("Udp test: please send \"begin test\" to the udp server, udp_state = %d.\n", udp_state);
                    continue;
                }
                int send_size = tuya_hal_net_send_to(udp_fd, "tuya api test", 13, client_ip_addr, client_port);
                if(send_size <= 0)
                {
                    PR_ERR(" Udp test: sendto the udp client fail, exit test.\n");
                    udp_state = 0;
                    break;
                }
                udp_state = 1;
                PR_WAR("Udp test: please send the string to server that you receive.\n");
            }
            else if(udp_state == 1)
            {
                if(strncmp(recv_buff, "tuya api test", 13) != 0)
                {
                    udp_state = 0;
                    PR_WAR("Udp test: please send \"begin test\" to the udp server.\n");
                    continue;
                }
                udp_state = 2;
                break;
            }
        }
    }
    if(udp_state != 2)
        ret = -1;
    tuya_hal_net_close(udp_fd);
    if(recv_buff){
        tuya_hal_system_free(recv_buff);
        recv_buff = NULL;
    }
    return ret;
}

int tuya_main(int argc, char *argv[])
{
    int ret = -1;
    printf("****************************************************\n");
    PR_DEBUG("Welcome to Tuya api test.\n");
    printf("****************************************************\n");

    //1、flash api操作测试
    ret = tuya_flash_api_test();
    if(ret != 0)
    {
        printf("****************************************************\n");
        PR_ERR(" flash api test err, exit...\n");
        printf("****************************************************\n");
        return -1;
    }
    else{
        printf("****************************************************\n");
        PR_WAR("flash api test success.\n");
        printf("****************************************************\n");
    }

    //2、memory api操作测试
    ret = tuya_memory_api_test();
    if(ret != 0)
    {   printf("****************************************************\n");
        PR_ERR(" memory api test err, exit...\n");
        printf("****************************************************\n");
        return -1;
    }
    else{
       printf("****************************************************\n");
       PR_WAR("memory api test success.\n");
       printf("****************************************************\n");
    }

    //3、thread api 操作测试
    ret = tuya_thread_api_test();
    if(ret != 0)
    {
        printf("****************************************************\n");
        PR_ERR(" thread api test err, exit...\n");
        printf("****************************************************\n");
        return -1;
    }
    else{
        printf("****************************************************\n");
        PR_WAR("thread api test success.\n");
        printf("****************************************************\n");
    }

    //4、mutex api 操作测试
    ret = tuya_mutex_api_test();
    if(ret != 0)
    {
        printf("****************************************************\n");
        PR_ERR(" mutex api test err, exit...\n");
        printf("****************************************************\n");
        return -1;
    }
    else{
        printf("****************************************************\n");
        PR_WAR("mutex test success.\n");
        printf("****************************************************\n");
    }

    //5、semaphore api 操作测试
    ret = tuya_semaphore_api_test();
    if(ret != 0)
    {
        printf("****************************************************\n");
        PR_ERR(" semaphore api test err, exit...\n");
        printf("****************************************************\n");
        return -1;
    }
    else{
        printf("****************************************************\n");
        PR_WAR("semaphore test success.\n");
        printf("****************************************************\n");
    }

    //6、配网流程模拟测试
    ret = tuya_network_test();
    if(ret != 0)
    {
        printf("****************************************************\n");
        PR_ERR(" connect network test err, exit...\n");
        printf("****************************************************\n");
        return -1;
    }

    //7、tcp/udp 通信测试
    ret = tuya_tcp_transmission_test();
    if(ret != 0)
    {
        printf("****************************************************\n");
        PR_ERR(" tcp transmission test err, exit...\n");
        printf("****************************************************\n");
        return -1;
    }
    else{
        printf("****************************************************\n");
        PR_ERR(" tcp transmission test success\n");
        printf("****************************************************\n");
    }

    ret = tuya_udp_transmission_test();
    if(ret != 0)
    {
        printf("****************************************************\n");
        PR_ERR(" udp transmission test err, exit...\n");
        printf("****************************************************\n");
        return -1;
    }
    else{
        printf("****************************************************\n");
        PR_WAR("Udp test: test success.\n");
        printf("****************************************************\n");
    }

    //8、枚举长度
    int length = sizeof(TUYA_TEST_TYPE_E);
    if(length != 4)
    {
        printf("****************************************************\n");
        PR_WAR("enum length is %d btyes, recommended to set it to 4 bytes");
        printf("****************************************************\n");
    }

    printf("****************************************************\n");
    PR_WAR("Tuya rtos api test ok.\n");
    printf("****************************************************\n");
    return 0;
}

