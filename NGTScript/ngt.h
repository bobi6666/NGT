#pragma once
#define _WINSOCKAPI_   /* Prevent inclusion of winsock.h in windows.h */
#include "Poco/URI.h"
#include "Poco/URIStreamOpener.h"
#include "Poco/StreamCopier.h"
#include "Poco/Net/HTTPClientSession.h"
#include "Poco/Net/HTTPRequest.h"
#include "Poco/Net/HTTPResponse.h"
#include "Poco/Base64Encoder.h"
#include "Poco/Base64Decoder.h"
#include "Poco/Base32Encoder.h"
#include "Poco/Base32Decoder.h"

#include "Poco/HexBinaryEncoder.h"
#include "Poco/HexBinaryDecoder.h"
#include "Poco/String.h"
#include "Poco/NumberFormatter.h"
#include"tts_voice.h"
using namespace Poco;
using namespace Poco::Net;
#include "dyn/dyncall.h"
#include "dyn/dynload.h"
#include <Windows.h>
#include "enet/enet.h"
#include <fcntl.h>
#include <io.h>
#include "sqlite3.h"
#include "scripthandle/scripthandle.h"
#include <random>
#include <type_traits>
#include<chrono>
#include <string>
//#define SDL_MAIN_HANDLED
#include"sdl/SDL.h"
#include <iostream>
#include<thread>
#include <vector>
#include "scriptdictionary/scriptdictionary.h"
using namespace std;
class ngtvector {
public:
	void construct();
	void destruct();
	float x, y, z;
	float get_length()const;
	ngtvector& operator=(const ngtvector);
};


wstring wstr(const string & utf8String);
uint64_t get_time_stamp_millis();
uint64_t get_time_stamp_seconds();
void as_printf(asIScriptGeneric* gen);
int get_cpu_count();
int get_system_ram();
string get_platform();
void set_exit_callback(asIScriptFunction* callback = nullptr);
void init_engine();
void set_library_path(const string& path);
long random(long min, long max);
 double randomDouble(double min, double max);
 bool random_bool();
 int get_last_error();
void speak(const string &	 text, bool stop = true);
void speak_wait(const string &	 text, bool stop = true);
void stop_speech();
string screen_reader_detect();
void show_console();
void hide_console();
bool show_window(const string & title,int width=640, int height=480, bool closable=true);
bool focus_window();
void hide_window();
void set_window_title(const string & );
void set_window_closable(bool);
bool get_window_active();
string key_to_string(SDL_Scancode);
SDL_Scancode string_to_key(const string&);
void garbage_collect();
void update_window(bool wait_event=false);
bool mouse_pressed(int);
bool mouse_down(int);
bool mouse_update();
int get_MOUSE_X();
int get_MOUSE_Y();
int get_MOUSE_Z();
void exit_engine(int=0);
string number_to_words(uint64_t, bool);
bool clipboard_copy_text(const string&);
string clipboard_read_text();
string get_input();
bool key_pressed(SDL_Scancode);
bool key_released(SDL_Scancode);
bool key_down(SDL_Scancode);
bool key_repeat(SDL_Scancode);
bool force_key_down(SDL_Scancode);
bool force_key_up(SDL_Scancode);
void reset_all_forced_keys();

SDL_Keycode* keys_pressed();
SDL_Keycode* keys_released();
SDL_Keycode* keys_down();
SDL_Keycode* keys_repeat();
string string_encrypt(string the_string, string encryption_key);
string string_decrypt(string the_string, string encryption_key);
string url_decode(const string& url);
string url_encode(const string& url);
string url_get(const string& url);
string url_post(const string& url, const string& parameters);
string ascii_to_character(int the_ascii_code);
int character_to_ascii(string the_character);
string hex_to_string(string the_hexadecimal_sequence);
string number_to_hex_string(double the_number);
string string_base64_decode(string base64_string);
string string_base64_encode(string the_string);
string string_base32_decode(string base32_string);
string string_base32_encode(string the_string);
string string_to_hex(string the_string);
bool alert(const string &	 title, const string &	 text, const string &button_name="OK");
int question(const string& title, const string &text);
void wait(uint64_t);
void delay(int);
string read_environment_variable(const string&);
void serialize(asIScriptGeneric*);
void deserialize(asIScriptGeneric*);
bool urlopen(const string& url);
class timer {
public:
	mutable int ref = 0;
	chrono::time_point<chrono::steady_clock> inittime;
	uint64_t pausedNanos = 0;

	timer() {
		inittime = chrono::steady_clock::now();
		pausedNanos = 0;
	}
	void construct();
	void destruct();
	uint64_t elapsed_seconds();
	uint64_t elapsed_minutes();
	uint64_t elapsed_hours();
	uint64_t elapsed_millis();
	uint64_t elapsed_micros();
	uint64_t elapsed_nanos();
	void force_seconds(uint64_t);
	void force_minutes(uint64_t);
	void force_hours(uint64_t);
	void force_millis(uint64_t);
	void force_micros(uint64_t);
	void force_nanos(uint64_t);
	void restart();
	void pause();
	void resume();
	bool is_running();
};
class network_event {
public:
    const int EVENT_NONE = ENET_EVENT_TYPE_NONE;
    const int EVENT_CONNECT = ENET_EVENT_TYPE_CONNECT;
    const int EVENT_RECEIVE = ENET_EVENT_TYPE_RECEIVE;
    const int EVENT_DISCONNECT = ENET_EVENT_TYPE_DISCONNECT;
	void construct();
	void destruct();
    int get_type() const {
        return m_type;
    }

unsigned    int get_peer_id() const {
        return m_peerId;
    }

unsigned    int get_channel() const {
        return m_channel;
    }

    string get_message() const {
        return m_message;
    }

    int m_type;
unsigned    int m_peerId;
    int m_channel;
    string m_message;
};

class network {
public:
	mutable int ref = 0;
	void construct();
	void destruct();
	unsigned    int connect(const string& host, int port);
	bool destroy();
	bool disconnect_peer(unsigned int);
	bool disconnect_peer_forcefully(unsigned int);
	bool disconnect_peer_softly(unsigned int);
	string get_peer_address(unsigned int);
	double get_peer_average_round_trip_time(unsigned int);
	CScriptArray* get_peer_list();
	network_event* request(int timeout=0, int *out_host_result=nullptr);
	bool send_reliable(unsigned int peerId, const string& packet, int channel);
	bool send_unreliable(unsigned int peerId, const string& packet, int channel);
	bool set_bandwidth_limits(double incomingBandwidth, double outgoingBandwidth);
	bool setup_client(int channels, int maxPeers);
	bool setup_server(int listeningPort, int channels, int maxPeers);

	int get_connected_peers() const;

	double get_bytes_sent() const;

	double get_bytes_received() const;

	bool is_active() const;

private:
	ENetAddress address;
	ENetHost* host;
	unsigned int current_peer_id;
	int m_connectedPeers;
	double m_bytesSent;
	double m_bytesReceived;
	bool m_active;
};
class library {
public:
	mutable int ref = 0;
	void* lib;
	void construct();
	void destruct();
	bool load(const string &);
		void unload();
};
void library_call(asIScriptGeneric* gen);
class script_thread {
private:
	mutable int ref = 0;
	asIScriptContext* context;
	asIScriptFunction* function;
	thread* th;
public:
	script_thread(asIScriptFunction* func);
	void join();
	void detach();
	void destroy();
};

class instance {
private:
	mutable int ref = 0;
	HANDLE mutex;
public:
	instance(const string & application_name) {
		mutex = CreateMutexA(NULL, TRUE, application_name.c_str());
	}
	void construct();
	void destruct();
	bool is_running();
	~instance() {
		CloseHandle(mutex);
	}
};
class user_idle {
public:
    user_idle();
    uint64_t elapsed_millis();  // Pridaná nová funkcia
    uint64_t elapsed_seconds();
    uint64_t elapsed_minutes();
    uint64_t elapsed_hours();
    uint64_t elapsed_days();
    uint64_t elapsed_weeks();

private:
    uint64_t get_idle_time();
};
class sqlite3statement
{
public:
	void construct();
	void destruct();
	int step();
	int reset();
	string get_expanded_sql_statement()const;
	string get_sql_statement() const;
	int get_bind_param_count()const;
	int get_column_count()const;
	int bind_blob(int index, const string& value, bool copy = true);
	int bind_double(int index, double value);
	int bind_int(int index, int value);
	int bind_int64(int index, int64_t value);
	int bind_null(int index);
	int bind_param_index(const string& name);
	string bind_param_name(int index);
	int bind_text(int index, const string& value, bool copy = true);
	int clear_bindings();
	string column_blob(int index);
	int column_bytes(int index);
	string column_decltype(int index);
	double column_double(int index);
	int column_int(int index);
	int64_t column_int64(int index);
	string column_name(int index);
	int column_type(int index);
	string column_text(int index);
	sqlite3_stmt* stmt;
};

using sqlite3_authorizer = int(*)(string, int, string, string, string, string);


class ngtsqlite3
{
public:
	void construct();
	void destruct();

	int close();
	int open(const string& filename, int flags = 6);
	sqlite3statement* prepare(const string& name, int& out);

	int execute(const string& sql);
	int64_t get_rows_changed() const;
	int64_t get_total_rows_changed()const;
	int limit(int id, int val);
	int set_authorizer(sqlite3_authorizer* callback, const string& arg = "");
	int64_t get_last_insert_rowid() const;
	void set_last_insert_rowid(int64_t id);
	int get_last_error();
	string get_last_error_text();
	bool get_active()const;
private:
	sqlite3* db;
};


