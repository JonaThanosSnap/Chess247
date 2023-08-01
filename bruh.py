import sys

name = sys.argv[1]
black_col = sys.argv[2].lower()
white_col = sys.argv[3].lower()
black_h_col = sys.argv[4].lower()
white_h_col = sys.argv[5].lower()
bg_col = sys.argv[6].lower()

print(f"""    // {name} Colors
    window.addColor(Color::{name}Black, "{black_col[:2]}", "{black_col[2:4]}", "{black_col[4:6]}");
    window.addColor(Color::{name}White, "{white_col[:2]}", "{white_col[2:4]}", "{white_col[4:6]}");
    window.addColor(Color::{name}BlackHighlight, "{black_h_col[:2]}", "{black_h_col[2:4]}", "{black_h_col[4:6]}");
    window.addColor(Color::{name}WhiteHighlight, "{white_h_col[:2]}", "{white_h_col[2:4]}", "{white_h_col[4:6]}");
    window.addColor(Color::{name}Bg, "{bg_col[:2]}", "{bg_col[2:4]}", "{bg_col[4:6]}");

    addTheme(BoardTheme{{
        "{name}",
        Color::{name}Black,
        Color::{name}White,
        Color::{name}BlackHighlight,
        Color::{name}WhiteHighlight,
        Color::{name}Bg,
        Color::{name}White
    }});
    
    {name}White,
    {name}Black,
    {name}BlackHighlight,
    {name}WhiteHighlight,
    {name}Bg,
""")