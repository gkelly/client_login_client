Introduction
============
client_login_client is a very lightweight [ClientLogin][1] authenticator, which
is useful for people building applications that want to use the [Google Data
Protocol][2].

client_login_client was designed to be as painless as possible to use, and only
depends on [libCURL][3], through which is supports authentication over SSL.

Example
=======
The API was designed to be exceptionally simple. The following is how you'd go
about authenticating an account and getting the [authentication token][4].

    client_login_client \*client = client_login_client_new();
    client_login_client_set_email(client, "fake_email_address@gmail.com");
    client_login_client_set_password(client, "fake_password");
    client_login_client_set_service(client, "jotspot");

    char \*auth_token;
    if (client_login_client_authenticate(client, &auth_token)) {
      // Authentication succeeded.
      delete(auth_token);
    }

[1]: http://code.google.com/apis/accounts/docs/AuthForInstalledApps.html
[2]: http://code.google.com/apis/gdata/
[3]: http://curl.haxx.se
[4]: http://code.google.com/apis/sites/docs/1.0/developers_guide_protocol.html#AuthClientLogin
