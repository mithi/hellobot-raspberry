"""
Run the app, redirect user to appropriate page
"""
import dash_core_components as dcc
import dash_html_components as html
from dash.dependencies import Input, Output
from settings import DEBUG_MODE
from style_settings import GLOBAL_PAGE_STYLE
from texts import URL_KOFI, URL_REPO
from app import app
from pages.old_pages import page_ik as old_ik
from pages.old_pages import page_ik2 as old_ik2
from pages import page_landing, page_kinematics

server = app.server

icon_link_style = {"margin": "0 0 0 0.5em"}
div_header = html.Div(
    [
        html.A(html.H6("👾"), href=URL_REPO, target="_blank", style=icon_link_style),
        html.A(html.H6("☕"), href=URL_KOFI, target="_blank", style=icon_link_style),
        dcc.Link(html.H6("●"), href="/", style=icon_link_style),
        dcc.Link(html.H6("●"), href="/kinematics", style=icon_link_style),
    ],
    style={"display": "flex", "flex-direction": "row"},
)

div_nav = html.Div(
    [
        html.Br(),
        html.A("👾 Source Code", href=URL_REPO, target="_blank"),
        html.Br(),
        html.A("☕ Buy Mithi coffee", href=URL_KOFI, target="_blank",),
        html.Br(),
        dcc.Link("● Root", href="/"),
        html.Br(),
        dcc.Link("● Kinematics", href="/kinematics"),
        html.Br(),
    ]
)

# --------------
# Layout
# --------------
app.layout = html.Div(
    [
        div_header,
        dcc.Location(id="url", refresh=False),
        html.Div(id="page-content"),
        div_nav,
    ],
    style=GLOBAL_PAGE_STYLE,
)

# --------------
# URL redirection
# --------------
PAGES = {
    "/kinematics": page_kinematics.layout,
    "/": page_landing.layout,
    "/ik-2": old_ik2.layout,
    "/ik-1": old_ik.layout,

}


@app.callback(Output("page-content", "children"), [Input("url", "pathname")])
def display_page(pathname):
    """
    Display to appropriate page content given url
    """
    try:
        return PAGES[pathname]
    except KeyError:
        return PAGES["/"]


# --------------
# Run server
# --------------
if __name__ == "__main__":
    app.run_server(
        debug=DEBUG_MODE, dev_tools_ui=DEBUG_MODE, dev_tools_props_check=DEBUG_MODE
    )
