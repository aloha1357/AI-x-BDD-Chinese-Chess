require 'rspec/expectations'

# Cucumber 環境設置
World(RSpec::Matchers)

# 全局設置
Before do
  puts "\n🎮 開始新的測試場景"
end

After do |scenario|
  if scenario.failed?
    puts "❌ 場景失敗: #{scenario.name}"
  else
    puts "✅ 場景通過: #{scenario.name}"
  end
end
