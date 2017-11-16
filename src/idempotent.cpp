#include "idempotent.h"

#include "MyRedis/redis_client.h"

Idempotent::Idempotent() :   _redis_client(new MyRedis::RedisClient()) {

}

bool Idempotent::init(const std::string& json_conf_str) {
	return _redis_client->init(json_conf_str);
}

bool Idempotent::can_handle(const std::string& prefix, const std::string& key) {
	std::string redis_key = prefix +"-" + key;
	int value = MyRedis::get_time_stamp();
	return _redis_client->set(redis_key, MyRedis::int2str(value), -1,
		MyRedis::RedisClient::SET_MODE_NX);
}

bool Idempotent::reset_handle(const std::string& prefix, const std::string& key) {
	std::string redis_key = prefix +"-" + key;
	int value = MyRedis::get_time_stamp();
	return _redis_client->del(redis_key);
}
