#ifndef _IDEMPOTENT_
#define _IDEMPOTENT_
#include <string>

namespace MyRedis {
class RedisClient;
}

class Idempotent{
public:
	Idempotent();
	bool init(const std::string& json_conf_str);
	bool can_handle(const std::string& key_type, const std::string& key);
	bool reset_handle(const std::string& key_type, const std::string& key);

private:
    MyRedis::RedisClient *_redis_client;
};

#endif //_IDEMPOTENT_
