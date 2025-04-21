# TMDB Movie Viewer

This is a simple C++ CLI application that fetches and displays movie information from The Movie Database (TMDb) API. It allows users to view different categories of movies such as:

- Now Playing
- Popular
- Top Rated
- Upcoming

## Requirements

- C++ Compiler (C++11 or later)
- libcurl
- JsonCpp

## Setup

1. **Install dependencies:**

   - **libcurl:**
     - On Ubuntu: `sudo apt-get install libcurl4-openssl-dev`
     - On macOS: `brew install curl`
   - **JsonCpp:**
     - On Ubuntu: `sudo apt-get install libjsoncpp-dev`
     - On macOS: `brew install jsoncpp`

2. **Clone this repository:**
git clone https://github.com/deniskhud/-TMDB-CLI-Tool-.git

3. **Compile the code:**

- Using g++:
  ```bash
  g++ -o tmdb-app main.cpp -lcurl -ljsoncpp
  ```

- Or if you are using Visual Studio or another IDE, make sure to link the necessary libraries (`libcurl` and `jsoncpp`).

## API Key

You need to provide your own API key to use the TMDb API. You can get one by signing up on the TMDb website [here](https://www.themoviedb.org/signup).

Once you have your API key, replace the `KEY_API` constant in the code with your own key:

```cpp
const string KEY_API = "your_api_key_here";
```

## Usage

To use this tool, compile the code and run the executable from the command line with the `--type` argument, followed by one of the following categories:

- **playing**: Fetches and displays movies that are currently playing in theaters.
- **popular**: Fetches and displays the most popular movies.
- **top**: Fetches and displays the top-rated movies.
- **upcoming**: Fetches and displays movies that will be released soon.

[project URL](https://roadmap.sh/projects/tmdb-cli)