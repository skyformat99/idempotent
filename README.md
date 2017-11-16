# 幂等接口
该幂等接口是借助redis中string结构实现，用户在处理消息前需要从redis中查询该消息是否存在，如果存在则进一步进行逻辑处理，否则视为已经处理过的接口。
技术实现：借助setnx，del接口实现去重表
# 接口

## 初始化接口
>**声明：bool Idempotent::init(const std::string& json_conf_str)**
>/*
>*参数：
> json_conf_str：redis配置，用于实现去重表
>*返回值：
>bool //true-->初始化成功，false-->失败
>*/

### redis配置格式
redis配置支持分片，集群，主从，需要写好配置文件即可。
如下配置：数据被分片存储到两个redis分片（key=0/1）中，每一个redis分片包含一主一从。
```
{
    "slice":[  //redis分片
        [//分片0
            {
                "key":0,//根据hash进行分片key
                "role":0,//该redis角色 0-->master, 1--->slave
                "host":"127.0.0.1", 
                "port":6379,
                "pwd":"",
                "conn_timeout":10, //连接超时时间秒
                "min_conn_count":20,//redis连接池初始大小
                "max_conn_count":100//redis动态增加的最大连接数
            },
            {
                "key":0,
                "role":1,
                "host":"127.0.0.1",
                "port":6379,
                "pwd":"",
                "conn_timeout":10,
                "min_conn_count":20,
                "max_conn_count":100
            }
        ],
        [//分片1
            {
                "key":1,
                "role":0,
                "host":"127.0.0.1",
                "port":6379,
                "pwd":"",
                "conn_timeout":10,
                "min_conn_count":20,
                "max_conn_count":100
            },
            {
                "key":1,
                "role":1,
                "host":"127.0.0.1",
                "port":6379,
                "pwd":"",
                "conn_timeout":10,
                "min_conn_count":20,
                "max_conn_count":100
            }
        ]
    ]
}
```

## 判定是否为已处理接口
>**声明：bool Idempotent::can_handle(const std::string& prefix, const std::string& key)**
>/*
>*参数：
prerfix：关键字前缀，防止key冲突，类似namespace功能，一般填写为key的类型（如：key或msg_id)
>key:消息唯一标识，和prefix一起唯一标识一个消息（prefix-key作为唯一消息标识）
>*返回值：
>bool //true-->消息未处理，false-->消息已经处理
*/


## 回滚消息接口
>**声明：bool Idempotent::reset_handle(const std::string& prefix, const std::string& key)**
>/*
>*参数：
prerfix：关键字前缀，防止key冲突，类似namespace功能，一般填写为key的类型（如：key或msg_id)
>key:消息唯一标识，和prefix一起唯一标识一个消息（prefix-key作为唯一消息标识）
>*返回值：
>bool //true-->回滚成功，false-->回滚失败
*/

## 依赖
1.hiredis
2.boost
3.MyRedis

## 使用实例
见：idempotent/test/main.cpp
