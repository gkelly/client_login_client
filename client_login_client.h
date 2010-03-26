// Copyright 2010 Garret Kelly, All Rights Reserved
// Author: gkelly@gkelly.org (Garret Kelly)

#ifndef CLIENT_LOGIN_CLIENT_H_
#define CLIENT_LOGIN_CLIENT_H_

#if defined(__cplusplus)
extern "C" {
#endif

typedef struct client_login_client client_login_client;

client_login_client *client_login_client_new();
void client_login_client_free(client_login_client *client);
void client_login_client_set_email(client_login_client *client,
    const char *email);
void client_login_client_set_password(client_login_client *client,
    const char *password);
void client_login_client_set_service(client_login_client *client,
    const char *service);
void client_login_client_set_source(client_login_client *client,
    const char *source);
int client_login_client_authenticate(client_login_client *client,
    char **auth_token);

#if defined(__cplusplus)
}
#endif

#endif
