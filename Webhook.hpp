#define CURL_STATICLIB
#include <curl/curl.h>
#include <iostream>
#include <string>

class Webhook {
public:
	Webhook() { curl_global_init(CURL_GLOBAL_DEFAULT); }
	~Webhook() { curl_global_cleanup(); }
	void file(const char* path);
	void message(const char* message);
	const char* get_url() { return url; }
private:
	const char* url = "https://discord.com/api/webhooks/1206612183509762079/Y2axClA-oykuX3wwHs0_vwv7tWtXoft42-aGeVmXn2hRKq1QsoNEJYwh99_Iq9D29eA7";
};