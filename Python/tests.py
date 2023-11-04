from unittest.mock import patch, call
from task_2 import create_field, main

side_effect = [
    "6 10",
    "0111000011",
    "0000011011",
    "0100011000",
    "0101011011",
    "0100000000",
    "0001111011",
]

error_side_effect = [
    "6 10",
    "0341000011",
    "0111000011",
    "0000011011",
    "0100011000",
    "0101011011",
    "0100000000",
    "00011110",
    "0001111011",
]


@patch("builtins.input", side_effect=side_effect)
def test_create_field(mock_input):
    field = create_field()

    expected_field = [
        [0, 1, 1, 1, 0, 0, 0, 0, 1, 1],
        [0, 0, 0, 0, 0, 1, 1, 0, 1, 1],
        [0, 1, 0, 0, 0, 1, 1, 0, 0, 0],
        [0, 1, 0, 1, 0, 1, 1, 0, 1, 1],
        [0, 1, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 1, 1, 1, 1, 0, 1, 1]
    ]

    assert field == expected_field


@patch("builtins.input", side_effect=side_effect)
@patch("builtins.print")
def test_main(mock_print, mock_input):
    main()

    expected_output = [
        "1 1 1",
        "2 1 2",
        "2 2 2",
        "3 1 2",
        "3 2 1",
        "4 1 1",
    ]

    mock_print.assert_has_calls([call(output) for output in expected_output])


@patch("builtins.input", side_effect=error_side_effect)
@patch("builtins.print")
def test_error_main(mock_print, mock_input):
    main()

    expected_output = [
        "Введите строку длиной 10, состоящую из 0 и 1",
        "Введите строку длиной 10, состоящую из 0 и 1",
        "1 1 1",
        "2 1 2",
        "2 2 2",
        "3 1 2",
        "3 2 1",
        "4 1 1",
    ]

    mock_print.assert_has_calls([call(output) for output in expected_output])
