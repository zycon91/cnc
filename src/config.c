#include "config.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ini.h>

#define CHECK_SECTION(s) strcmp(section, s) == 0
#define MATCH(s, n) strcmp(section, s) == 0 && strcmp(name, n) == 0

config_t *ini_config;

static int handler(void *user, const char *section, const char *name,
		   const char *value)
{
	ini_config = (config_t *)user;

	if (CHECK_SECTION("postgres")) {
		if (MATCH("postgres", "enabled")) {
			if (strcmp(value, "true") == 0)
				ini_config->postgres_config->enabled = true;
			else
				ini_config->postgres_config->enabled = false;
		}

		// Origin
		if (MATCH("postgres", "origin_host")) {
			ini_config->postgres_config->origin_host =
				strdup(value);
		} else if (MATCH("postgres", "origin_user")) {
			ini_config->postgres_config->origin_user =
				strdup(value);
			printf("%s\n",
			       ini_config->postgres_config->origin_user);
		} else if (MATCH("postgres", "origin_password")) {
			ini_config->postgres_config->origin_password =
				strdup(value);
		} else if (MATCH("postgres", "origin_port")) {
			ini_config->postgres_config->origin_port =
				strdup(value);
		} else if (MATCH("postgres", "origin_database")) {
			ini_config->postgres_config->origin_database =
				strdup(value);
		}

		// Target
		if (MATCH("postgres", "target_host")) {
			ini_config->postgres_config->target_host =
				strdup(value);
		} else if (MATCH("postgres", "target_user")) {
			ini_config->postgres_config->target_user =
				strdup(value);
		} else if (MATCH("postgres", "target_password")) {
			ini_config->postgres_config->target_password =
				strdup(value);
		} else if (MATCH("postgres", "target_port")) {
			ini_config->postgres_config->target_port =
				strdup(value);
		} else if (MATCH("postgres", "target_database")) {
			ini_config->postgres_config->target_database =
				strdup(value);
		}
	}

	// SMTP
	if (CHECK_SECTION("smtp")) {
		if (MATCH("smtp", "username")) {
			ini_config->smtp_config->username = strdup(value);
		} else if (MATCH("smtp", "password")) {
			ini_config->smtp_config->password = strdup(value);
		} else if (MATCH("smtp", "smtp_host")) {
			ini_config->smtp_config->smtp_host = strdup(value);
		} else if (MATCH("smtp", "smtp_port")) {
			ini_config->smtp_config->smtp_port = strdup(value);
		} else if (MATCH("smtp", "auth_mode")) {
			if (strcmp("ssl", value))
				ini_config->smtp_config->auth_mode = SSL;
			if (strcmp("tls", value))
				ini_config->smtp_config->auth_mode = TLS;
		}
	}

	return 1;
}

/* 
 * initialize_config
 *
 *   0 Success
 *  -1 Error reading file
 *  -2 Error parsing file
 *
 */
int initialize_config(const char *config_file)
{
	int ret = 0;

	ini_config = (config_t *)malloc(sizeof(config_t));
	ini_config->postgres_config = (postgres_t *)malloc(sizeof(postgres_t));
	ini_config->smtp_config = (smtp_t *)malloc(sizeof(smtp_t));

	if (ini_parse("test.ini", handler, ini_config) < 0) {
		return -1;
	}

	return ret;
}

void free_config(void)
{
	free((void *)ini_config->postgres_config->origin_host);
	free((void *)ini_config->postgres_config->origin_user);
	free((void *)ini_config->postgres_config->origin_password);
	free((void *)ini_config->postgres_config->origin_port);
	free((void *)ini_config->postgres_config->origin_database);

	free((void *)ini_config->postgres_config->target_host);
	free((void *)ini_config->postgres_config->target_user);
	free((void *)ini_config->postgres_config->target_password);
	free((void *)ini_config->postgres_config->target_port);
	free((void *)ini_config->postgres_config->target_database);

	free((void *)ini_config->smtp_config->username);
	free((void *)ini_config->smtp_config->password);
	free((void *)ini_config->smtp_config->smtp_host);

	free(ini_config->smtp_config);
	free(ini_config->postgres_config);
	free(ini_config);
}
