1. if u are taking lock on some mutex,
ensure to notify the cv linked to that mutex at work end
2. always have stopped bool