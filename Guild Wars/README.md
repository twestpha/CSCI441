
<h1> Guild Wars </h1>

<h2> Git procedure </h2>

When beginning a new feature or bug fix, create a new branch inside the repository, using

`git checkout -b [name_of_your_new_branch]`

and then push this information to the repository by using

`git push origin [name_of_your_new_branch]`

When you feel that the feature is completed, create a pull request from the github website. This will automatically evaluate the mergeability of the code, as well as making it easy to look over.

Another team member will merge the code as soon as possible, thus admitting it to the codebase. This will prevent us from colliding when merging to and from the same master repository.

When merging someone else's pull request, read over their code lightly, looking for any obvious inconsistencies or style problems. We don't care too much, just a glance will do.

Check to make sure the code can be automatically merged. If it can, merge the pull request and delete the branch. If it cannot, notify the author of the code and ask that they merge `[master]` into `[name_of_your_new_branch]` (Not the other way around!).

Having merged master into their branch, they may now push to that branch. This will allow it to be automatically merged, and the pull request can be closed. Don't forget to delete the branch!

<h2> Filenames and Style Standards </h2>
Class header (.hpp) and implementation (.cpp) files should have the same name as their respective class. For example, the `Drawable` class header is named "Drawable.hpp" and the implementation is named "Drawable.cpp"

When possible, try to ensure that each header is only responsible for one class.

Do not put implementation code in the header file, unless necessary.
