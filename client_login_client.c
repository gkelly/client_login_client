// Copyright 2010 Garret Kelly, All Rights Reserved
// Author: gkelly@gkelly.org (Garret Kelly)

#include "client_login_client.h"

#include <curl/curl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const char *kClientLoginUrl =
    "https://www.google.com/accounts/ClientLogin";
static const char *kEmail = "Email";
static const char *kPassword = "Passwd";
static const char *kService = "service";
static const char *kSource = "source";
static const char *kAuthStart = "Auth=";

struct client_login_client {
  char *email;
  char *password;
  char *service;
  char *source;
};

client_login_client *client_login_client_new() {
  client_login_client *client =
    (client_login_client *)malloc(sizeof(client_login_client));

  client->email = NULL;
  client->password = NULL;
  client->service = NULL;
  client->source = NULL;

  return client;
}

void client_login_client_free(client_login_client *client) {
  free(client->email);
  free(client->password);
  free(client->service);
  free(client->source);
  free(client);
}

void client_login_client_set_email(client_login_client *client,
    const char *email) {
  free(client->email);
  client->email = strdup(email);
}

void client_login_client_set_password(client_login_client *client,
    const char *password) {
  free(client->password);
  client->password = strdup(password);
}

void client_login_client_set_service(client_login_client *client,
    const char *service) {
  free(client->service);
  client->service = strdup(service);
}

void client_login_client_set_source(client_login_client *client,
    const char *source) {
  free(client->source);
  client->source = strdup(source);
}

int client_login_client_authenticate(
    client_login_client *client, char **auth_token) {
  struct curl_httppost *post = NULL;
  struct curl_httppost *last = NULL;
  curl_formadd(&post, &last, CURLFORM_PTRNAME, kEmail,
      CURLFORM_PTRCONTENTS, client->email, CURLFORM_END);
  curl_formadd(&post, &last, CURLFORM_PTRNAME, kPassword,
      CURLFORM_PTRCONTENTS, client->password, CURLFORM_END);
  curl_formadd(&post, &last, CURLFORM_PTRNAME, kService,
      CURLFORM_PTRCONTENTS, client->service, CURLFORM_END);
  if (client->source) {
    curl_formadd(&post, &last, CURLFORM_PTRNAME, kSource,
        CURLFORM_PTRCONTENTS, client->source, CURLFORM_END);
  }

  char *response = NULL;
  size_t response_length;
  FILE *response_stream = open_memstream(&response, &response_length);
  if (!response_stream) {
    curl_formfree(post);
    return 0;
  }

  CURL *curl_handle = curl_easy_init();
  curl_easy_setopt(curl_handle, CURLOPT_URL, kClientLoginUrl);
  curl_easy_setopt(curl_handle, CURLOPT_HTTPPOST, post);
  curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, response_stream);
  curl_easy_perform(curl_handle);
  curl_easy_cleanup(curl_handle);
  curl_formfree(post);

  fclose(response_stream);
  char *auth_value_start = strstr(response, kAuthStart);
  if (!auth_value_start) {
    free(response);
    return 0;
  }

  char *auth_value_end = strchr(auth_value_start, '\n');
  if (!auth_value_end) {
    free(response);
    return 0;
  }
  *auth_value_end = '\0';
  *auth_token = strdup(auth_value_start + strlen(kAuthStart));

  free(response);
  return 1;
}
