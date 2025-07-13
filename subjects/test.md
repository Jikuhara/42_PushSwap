flowchart LR
    start(["get_next_line(fd)"])

    check["fd チェック<br/>fd < 0 &#124;&#124; fd >= OPEN_MAX &#124;&#124; BUFFER_SIZE <= 0"]
    init_check["static_bufs[fd] == NULL ?"]
    init["初期読み込み<br/>init_buffer(fd)"]
    extract["行の抽出<br/>extract_line(&amp;static_bufs[fd])"]
    readloop["読み込みループ<br/>read_line_loop(fd, &amp;static_bufs[fd], buffer)"]
    return_line["return line"]
    output["出力<br/>1行の文字列 or NULL"]
    null1["return NULL"]
    null2["return NULL"]

    start --> check
    check -- "NG" --> null1
    check -- "OK" --> init_check

    init_check -- "yes" --> init
    init_check -- "no"  --> extract

    init -- "fail"    --> null2
    init -- "success" --> extract

    extract -- "line あり" --> return_line
    extract -- "NULL"      --> readloop

    readloop --> output
    return_line --> output
    null1 --> output
    null2 --> output
