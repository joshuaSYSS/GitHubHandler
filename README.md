# GitHubHandler
C++ Library offerring simple and easy to use commands to push files.

# How to use:

```#include "the_absolute_path/githubhandle.cpp"```

# Commands

Has the user logged in?
```
bool checkgitauth()
```

Attempt to login. Please include the token in a file and place the path here.
```
void gitauth(const char* authTokenPath)
```

Attempt to push a file.
```
std::string gitpush(const char filePath[])
```
