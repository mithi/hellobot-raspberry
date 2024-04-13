"""
One graph and one sidebar
"""
import dash_core_components as dcc
from dash.dependencies import Output, Input, State
import dash_html_components as html
from pages.shared import DIMS_JSON_CALLBACK_INPUT

# ......................
# Make uniform layout
# One Graph on the right, one sidebar
# ......................


def make_page_layout(graph_id, sidebar, base_figure):
    div_sidebar = html.Div(sidebar, style={"width": "25%"})
    graph = dcc.Graph(id=graph_id, figure=base_figure, style={"width": "75%"})
    layout = html.Div([div_sidebar, graph], style={"display": "flex"},)
    return layout

# ......................
# Make callbacks params
# ......................


def make_callback_params(
    graph_id,
    params_hidden_section_id,
    message_section_id,
):

    outputs = [
        Output(graph_id, "figure"),
        Output(message_section_id, "children"),
    ]

    inputs = [DIMS_JSON_CALLBACK_INPUT, Input(params_hidden_section_id, "children")]

    states = [
        State(graph_id, "relayoutData"),
        State(graph_id, "figure")
    ]

    return outputs, inputs, states
