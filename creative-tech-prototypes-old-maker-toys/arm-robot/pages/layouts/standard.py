import dash_core_components as dcc
from dash.dependencies import Output, Input, State
import dash_html_components as html
from widgets.dimensions_ui import DIMENSION_WIDGETS_SECTION
from arm.const import BASE_FIGURE2D_SIDE, BASE_FIGURE2D_TOP, BASE_FIGURE3D
from pages.shared import DIMENSIONS_HIDDEN_SECTION, DIMS_JSON_CALLBACK_INPUT

# ......................
# Make standard sidebar section
# ......................


def make_sidebar(params_widgets_section, params_hidden_section_id, message_section_id):
    params_hidden_section = html.Div(
        id=params_hidden_section_id, style={"display": "none"}
    )
    message_section = html.Div(id=message_section_id)

    return [
        DIMENSION_WIDGETS_SECTION,
        params_widgets_section,
        params_hidden_section,
        DIMENSIONS_HIDDEN_SECTION,
        message_section,
    ]


# ......................
# Make uniform layout
# Graph on the right, controls on the left
# ......................
def make_page_layout(graph_side_id, graph_top_id, graph_3d_id, sidebar):

    div_sidebar = html.Div(sidebar, style={"width": "25%"})

    graph_side = dcc.Graph(
        id=graph_side_id, figure=BASE_FIGURE2D_SIDE, style={"height": "310px"}
    )

    graph_top = dcc.Graph(
        id=graph_top_id, figure=BASE_FIGURE2D_TOP, style={"height": "310px"}
    )

    graph3d = dcc.Graph(id=graph_3d_id, figure=BASE_FIGURE3D, style={"width": "55%"})
    graphs2d = html.Div([graph_side, graph_top], style={"width": "20%"})

    layout = html.Div([div_sidebar, graphs2d, graph3d], style={"display": "flex"},)
    return layout


# ......................
# Make standard callbacks params
# ......................


def make_callback_params(
    graph_side_id,
    graph_top_id,
    graph_3d_id,
    params_hidden_section_id,
    message_section_id,
):
    graph_ids = [graph_side_id, graph_top_id, graph_3d_id]

    outputs = [
        Output(graph_side_id, "figure"),
        Output(graph_top_id, "figure"),
        Output(graph_3d_id, "figure"),
        Output(message_section_id, "children"),
    ]

    inputs = [DIMS_JSON_CALLBACK_INPUT, Input(params_hidden_section_id, "children")]

    relayout_states = [State(id, "relayoutData") for id in graph_ids]
    figure_states = [State(id, "figure") for id in graph_ids]
    states = relayout_states + figure_states

    return outputs, inputs, states
