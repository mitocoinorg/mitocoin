Bolsonarocoin Core integration/staging tree
=====================================


https://

What is Bolsonarocoin?
----------------

Bolsonarocoin is an experimental test digital currency based on LiteCoin version 0,13.
It keeps all its main characteristics creating just a new genesis block, and some small modifications.

For more information, as well as an immediately useable, binary version of
the Bolsonarocoin Core software, see [https://.

License
-------


Development Process
-------------------



Testing
-------



### Automated Testing



### Manual Quality Assurance (QA) Testing

Changes should be tested by somebody other than the developer who wrote the
code. This is especially important for large or high-risk changes. It is useful
to add a test plan to the pull request description if testing the changes is
not straightforward.

Translations
------------

We only accept translation fixes that are submitted through [Bitcoin Core's Transifex page](https://www.transifex.com/projects/p/bitcoin/).
Translations are converted to Bolsonarocoin periodically.

Translations are periodically pulled from Transifex and merged into the git repository. See the
[translation process](doc/translation_process.md) for details on how this works.

**Important**: We do not accept translation changes as GitHub pull requests because the next
pull from Transifex would automatically overwrite them again.
