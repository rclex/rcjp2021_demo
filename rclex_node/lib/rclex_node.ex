defmodule RclexNode do
  def pub(num_node) do
    Rclex.rclexinit()
    |> Rclex.create_nodes('rclex_node', num_node)
    |> Rclex.create_publishers('chatter', :single)
    |> Rclex.Timer.timer_start(1000, &func/1)
  end

  def func(publisher_list) do
    n = length(publisher_list)
    msg_list = Rclex.initialize_msgs(n, :string)
    Enum.map(0..(n - 1), fn index ->
      data = "Hello World from rclex_node_" <> to_string(index)
      IO.puts("publish message: #{data}")
      Rclex.setdata(Enum.at(msg_list, index), data, :string)
    end)

    Rclex.Publisher.publish(publisher_list, msg_list)
  end
end