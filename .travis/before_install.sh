#!/bin/bash

set -e
set -x

# Example of how to run python on mac os x in travis from https://github.com/conan-io/hooks/blob/master/.travis/before_install.sh
if [ "$TRAVIS_OS_NAME" == "osx" ]; then
    brew update
    brew install openssl readline

    brew outdated pyenv || brew upgrade pyenv
    brew install pyenv-virtualenv

    if which pyenv > /dev/null; then eval "$(pyenv init -)"; fi
    if which pyenv-virtualenv > /dev/null; then eval "$(pyenv-virtualenv init -)"; fi

    pyenv install 3.7.0
    pyenv virtualenv 3.7.0 conan

    pyenv rehash
    pyenv activate conan

    python --version
fi
