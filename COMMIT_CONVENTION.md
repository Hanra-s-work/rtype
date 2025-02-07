# Commit convention

This file will describe the norm used for commits in this repository.

This repository does not use the conventional commit down to the letter.

---

## Commit Message Convention

Each commit message must follow one of the format below:

- `[uppercase infinitive verb] <concise description>`

Additional details about the commit sections:

- **Prefix**: The commit message should always begin with an action verb in its infinitive form. The verb should describe the type of change being made.
- **Description**: After the verb, provide a brief description of what has been done in that commit. Avoid past tense or gerunds (form of a verb that ends in "-ing" and functions as a noun in a sentence).
- **Body (Optional)**: There are no specific rules for the commit body. You can add details as necessary in subsequent lines.

### Examples

- `[ADD] a new service endpoint for user management`
- `[FIX] login endpoint handling edge cases`
- `[UPDATE] documentation with new examples`
- `[REFACTOR] client code part`
- `[REMOVE] redundant code from the user service`
- `[EDIT] UI to match updated mockups`
- `[RENAME] Readme.md -> README.md`

### Additional Notes

- **Prefixes** should always be in uppercase to clearly identify the action if they are encapsulated by `[]`, however, if they are followed not encapsulated by `[]` and followed by a `:` they should be in lowercase.
- Try to keep descriptions concise and to the point. Use the body for further elaboration if needed.
- If the commit is related to workflows or external dependencies, be explicit in the description.

### Examples from this Repository

- `[ADD] a window utility management class`
- `[ADD] a window that can open`
- `[FIX] exception handling issues`
- `[UPDATE] the type of the mainloop function`
