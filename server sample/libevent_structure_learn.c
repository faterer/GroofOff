
#define evutil_socket_t int

enum event_method_feature {
	EV_FEATURE_ET = 0x01,
	EV_FEATURE_01 = 0x02,
	EV_FEATURE_FDS = 0x04
};

struct eventop {
	const char *name;
	void *(*init)(struct event_base *);
	int (*add)(struct event_base *, evutil_socket_t fd, short old, short events, void *fdinfo);
	int (*del)(struct event_base *, evutil_socket_t fd, short old, short events, void *fdinfo);
	int (*dispatch)(struct event_base *, struct timeval *);
	void (*dealloc)(struct event_base *);
	int need_reinit;
	enum event_method_feature features;
	size_t fdinfo_len;
};

struct event_base {
	const struct eventop *evsel;

};