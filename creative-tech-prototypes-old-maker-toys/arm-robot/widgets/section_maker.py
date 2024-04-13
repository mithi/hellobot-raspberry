"""
Used to make html divsions
"""
import dash_html_components as html


def make_section_type3(div1, div2, div3, name1="", name2="", name3=""):
    """
    Returns an html div with three columns of equal widths,
    one column for each div passed as an argument.
    """
    return html.Div(
        [
            html.Div([div1, name1], style={"width": "33%"}),
            html.Div([div2, name2], style={"width": "33%"}),
            html.Div([div3, name3], style={"width": "33%"}),
        ],
        style={"display": "flex"},
    )


def make_section_type2(div1, div2, name1="", name2=""):
    """
    Returns an html div with two columns of equal widths,
    one column for each div passed as an argument.
    """
    return html.Div(
        [
            html.Div([div1, name1], style={"width": "50%"}),
            html.Div([div2, name2], style={"width": "50%"}),
        ],
        style={"display": "flex"},
    )


def make_section_type4(div1, div2, div3, div4, name1="", name2="", name3="", name4=""):
    """
    Returns an html div with four columns of equal widths,
    one column for each div passed as an argument.
    """
    return html.Div(
        [
            html.Div([div1, name1], style={"width": "25%"}),
            html.Div([div2, name2], style={"width": "25%"}),
            html.Div([div3, name3], style={"width": "25%"}),
            html.Div([div4, name4], style={"width": "25%"}),
        ],
        style={"display": "flex"},
    )
