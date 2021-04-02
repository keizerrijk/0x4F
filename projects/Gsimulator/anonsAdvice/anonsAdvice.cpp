std::string getNonemptyInput()
{
  std::string in = "";
  while(!in.empty())
  {
    std::cout << "Error: please enter a valid meme image.";
    cin >> usrInput;
  }
  std::transform(usrInput.begin(), usrInput.end(), usrInput.begin(), std::tolower);
  return in;
}

string imgChoice() {
  // If you alphabetize them, then you can do a binary search over the names.
  static const std::vector<std::string> NAMES {
    "cheems",
    "coomer",
    "doge",
    "peter",
    "troll",
    "walter",
  };

  bool found_meme = false;
  std::string user_input = getNonemptyInput();
  while(!found_meme)
  {
    auto iter = std::binary_search(NAMES.cbegin(), NAMES.cend, usrInput);

    // If iter is NAMES.cend(), then the name was not found. Try again.
    if(iter != NAMES.cend())
    {
      found_meme = true;
    }
    else
    {
      std::cout << "Unable to recognize image... Try again" << std::endl;
      usrInput = getNonemptyInput();
    }
  }

  return usrInput;
}
